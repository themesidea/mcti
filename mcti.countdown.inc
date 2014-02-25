<?php
/**
 * @file
 * This file provides theme part of MCTI module
 */

/**
 * Implements of hook_theme_registry_alter().
 *
 * Make drupal to use this maintenance-countdown-page.tpl.php in
 * maintenance mode if timer is set
 *
 * @param $theme_registry
 * The entire cache of theme registry information, post-processing.
 */
function mcti_theme_registry_alter(&$theme_registry) {
  // If site doing process like install or update don't use this template
  if (isset($theme_registry['maintenance_page']) && !defined('MAINTENANCE_MODE')) {
    $theme_registry['maintenance_page']['path'] = drupal_get_path('module', 'mcti');
    $theme_registry['maintenance_page']['template'] = 'maintenance-countdown-page';
//  Type should be 'theme' to prevent fatal error like:
//  can't call undefined fnc system_rebuild_MODULE_data()
    $theme_registry['maintenance_page']['type'] = 'theme';
  }
}


/**
 * Generate the jQuery output
 */
function mcti_js_countdown() {
//  get stoptime like 1315776380
  $stoptime = variable_get('mcti_stoptime');
  $mcti_message = variable_get('mcti_time_up_message', FALSE);
  $mcti_reload = variable_get('mcti_reload_button', 0);
//  jQuery script for countdown initialization
  $output = "jQuery(document).ready(function($) {\$('#countdown_dashboard').countDown({targetDate: {";
  $output .= "'day': " .
      format_date($stoptime, 'custom', "j") . ", 'month': " .
      format_date($stoptime, 'custom', "n") . ", 'year': " .
      format_date($stoptime, 'custom', "Y") . ", 'hour': " .
      format_date($stoptime, 'custom', "G") . ", 'min': " .
      format_date($stoptime, 'custom', "i") . ", 'sec': " .
      format_date($stoptime, 'custom', "s") . ", 'utc': '" .
      format_date($stoptime, 'custom', "O") . "'}";
  if ($mcti_message || $mcti_reload != 1) {
    $output .= ", onComplete: function() {";
//  slide down 'time is up' message or 'Reload' button
    if ($mcti_message || $mcti_reload == 0) {
      $output .= " \$('#complete_message').slideDown();";
    }
    if ($mcti_reload == 2) {
      $output .= " setTimeout(function() {location.reload();}, 15000)";
    }
    $output .= "}";
  }
// close countDown
  $output .= "});";
//  reload current page by clicking 'Reload' button
  if (variable_get('mcti_reload_button', 0) == 0) {
    $output .= "\$('#page_reload').click(function() {location.reload()});";
  }
// close function
  $output .= "\$('#countdown_dashboard2').startCountDown();";
  $output .= "});";
  return $output;
}


/**
 * Add some variables for maintenance-coundown-page.tpl.php file.
 * You can override this or core or add custom variables via your theme
 * just using the same TEMPLATE_preprocess_maintenance_page
 * @param $variables
 */
function mcti_preprocess_maintenance_page(&$variables) {
  $path = drupal_get_path('module', 'mcti');
  $variables['css'] = array();
  drupal_add_css(drupal_get_path('module', 'mcti') . '/styles/maintenance-page.css');

//   CUT unneeded js files! Yay! Should work as magic...
  $js = drupal_add_js();
  array_splice($js, 4);
  $variables['js'] = drupal_get_js('header', $js);

  $variables['mcti_js'] = '<script src="' . $GLOBALS['base_url'] . '/' .
    drupal_get_path('module', 'mcti') . '/js/jquery.lwtCountdown-1.0-min.js' . "\"></script>\n";
  $variables['mcti_js_countdown'] = mcti_js_countdown();

  if (variable_get('mcti_site_logo') == 1) {
    unset($variables['logo']);
  }
  if (variable_get('mcti_site_name') == 1) {
    unset($variables['site_name']);
  }
  if (variable_get('mcti_site_slogan') == 1) {
    unset($variables['site_slogan']);
  }

//  add theme css
  drupal_add_css(drupal_get_path('module', 'mcti') . '/styles/' . variable_get('mcti_page_themes', 'galaxy') . '.css', array(
    'type' => 'file',
    'group' => CSS_THEME,
    'every_page' => FALSE,
    'weight' => 99,
    'preprocess' => FALSE)
  );

  $variables['time_up_message'] = variable_get('mcti_time_up_message', FALSE);

  $twitter_username = variable_get('twitter_username');
  $facebook_url     = variable_get('facebook_url');
  $google_plus_url  = variable_get('google_plus_url');
  $linkedin_url     = variable_get('linkedin_url');
  $dribble          = variable_get('dribble');
  $flickr_url       = variable_get('flickr_url');
  $vimeo_url        = variable_get('vimeo_url');

  $follow = '';
  $follow .= '<ul class="maintenance-social-links">';
  if (!empty ($twitter_username)) { $follow .= '<li><a class="social-tooltip" href="http://twitter.com/"'. $twitter_username .'" title="'.t('Twitter').'" rel="nofollow"><i class="fa fa-twitter"></i></a></li>'; }
  if (!empty ($facebook_url)) { $follow .= '<li><a class="social-tooltip" href="'. $facebook_url .'" title="'.t('Facebook').'" rel="nofollow"><i class="fa fa-facebook"></i></a></li>'; }
  if (!empty ($google_plus_url)) { $follow .= '<li><a class="social-tooltip" href="'. $google_plus_url .'" title="'.t('Gplus').'" rel="nofollow"><i class="fa fa-google-plus"></i></a></li>'; }
  if (!empty ($linkedin_url)) { $follow .= '<li><a class="social-tooltip" href="'. $linkedin_url .'" title="'.t('linkedin').'" rel="nofollow"><i class="fa fa-linkedin"></i></a></li>'; }
  if (!empty ($dribble)) { $follow .= '<li><a class="social-tooltip" href="'. $dribble .'" title="'.t('Dribble').'" rel="nofollow"><i class="fa fa-dribbble"></i></a></li>'; }
  if (!empty ($flickr_url)) { $follow .= '<li><a class="social-tooltip" href="'. $flickr_url .'" title="'.t('Flickr').'" rel="nofollow"><i class="fa fa-flickr"></i></a></li>'; }
  if (!empty ($vimeo_url)) { $follow .= '<li><a class="social-tooltip" href="'. $vimeo_url .'" title="'.t('Vimeo').'" rel="nofollow"><i class="fa fa-vimeo-square"></i></a></li>'; }
  $follow .= '</ul>';

  $variables['follow_block'] = '';
  $variables['copyright_block'] = '';
  $variables['follow_block'] = $follow;
  $variables['copyright_block'] = '<div id="copyright-block">' .t('Copyright ©@website 2014. All rights reserved.', array('@website' => $variables['site_name'])). '</div>';


  if (variable_get('mcti_reload_button', 0) == 0) {
    $variables['reload_button'] = l(t('♻ Reload'), $_GET['q'] , array(
        'attributes' => array(
            'id' => 'page_reload',
            'title' => t('Reload this page')
        )));
  }
  else {
    $variables['reload_button'] = FALSE;
  }

  if (mcti_check_simplenews() && variable_get('mcti_email_subscr', 0) != 0) {
    $block = module_invoke('simplenews', 'block_view', variable_get('mcti_email_subscr'));
    $variables['subsc'] = render($block['content']);
  }
}
