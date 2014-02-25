<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in html.tpl.php and page.tpl.php.
 * Some may be blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $js; ?>
</head>
<body class="<?php print $classes; ?>">
  <div id="page">
    <div id="header">
      <div class="container group">
        <div class="container-inner">
          <div class="group pad">
            <?php if ($logo): ?>
              <h1 class="site-title">
                <a href="<?php print $base_path; ?>" title="<?php print t('Phoenix'); ?>" rel="home">
                  <img src="<?php print file_create_url($logo); ?>" alt="<?php print t('Phoenix'); ?>" />
                </a>
              </h1>
            <?php endif; ?>
            <?php if ($site_name || $site_slogan): ?>
                <?php if ($site_name): ?>
                  <h1 class="site-title">
                    <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
                  </h1>
                <?php endif; ?>

                <?php if ($site_slogan): ?>
                  <p class="site-description"><?php print $site_slogan; ?></p>
                <?php endif; ?>

            <?php endif; ?>

            <?php if (!empty($header)): ?>
              <div id="header-region">
                <?php print $header; ?>
              </div>
            <?php endif; ?>

          </div>
        </div><!--/.container-inner-->
      </div><!--/.container-->
    </div> <!-- /header -->

    <div id="content-page" class="container">
			<div class="container-inner">
				<div class="main">
          <div class="main-inner group">
					  <section class="content">
						  <?php if (!empty($messages)): print $messages; endif; ?>
						  <div id="content-content" class="clearfix">
							  <h2 id="mcti-block-title" class="block-title"><?php print $content . t(' <em>but</em>, we\'ll be back in:'); ?></h2>

                <!-- Countdown Container : Start-->
                <div id="countdown_dashboard" class="clear-block">

                  <div class="dash weeks_dash">
                    <span class="dash_title_weeks"><?php print t('weeks')?></span>
                    <div class="digit"></div>
                    <div class="digit"></div>
                  </div>

                  <div class="dash days_dash">
                    <span class="dash_title_days"><?php print t('days')?></span>
                    <div class="digit"></div>
                    <div class="digit"></div>
                  </div>

                  <div class="dash hours_dash">
                    <span class="dash_title_hours"><?php print t('hours')?></span>
                    <div class="digit"></div>
                    <div class="digit"></div>
                  </div>

                  <div class="dash minutes_dash">
                    <span class="dash_title_minutes"><?php print t('minutes')?></span>
                    <div class="digit"></div>
                    <div class="digit"></div>
                  </div>

                  <div class="dash seconds_dash">
                    <span class="dash_title_seconds"><?php print t('seconds')?></span>
                    <div class="digit"></div>
                    <div class="digit"></div>
                  </div>

                </div>
                <!-- Countdown Container : End -->

                <?php if (!empty($subsc)): ?>
                  <div class="subscribe-email-form"><div class="email-inner">
                      <?php print $subsc; ?>
                    </div></div>
                <?php endif; ?>

                <?php if ($time_up_message || $reload_button): ?>
                  <div id="complete_message" class="clear-block">
                    <?php if ($time_up_message) : print $time_up_message; endif; ?>
                    <?php if ($reload_button) : print $reload_button; endif; ?>
                  </div>
                <?php endif; ?>

						  </div> <!-- /content-content -->
					  </section> <!-- /content -->
				  </div> <!-- /main-inner group -->
        </div> <!-- /main -->
			</div> <!-- /content-inner -->
    </div> <!-- /content -->


    <footer id="footer">
      <section id="footer-bottom" class="container">
        <div class="container-inner">
          <div class="pad group">
            <?php if (!empty($footer)): print $footer; endif; ?>
            <div class="grid one-half">
              <div id="copyright">
                <?php print $copyright_block; ?>
              </div><!--/#copyright-->
            </div>
            <div class="grid one-half last">
              <?php print $follow_block; ?>
            </div>
          </div><!--/.pad-->
        </div><!--/.container-inner-->
      </section><!--/.container-->
    </footer>

  </div> <!-- /page -->
  <?php print $mcti_js; ?>
  <script type="text/javascript">
    <!--//--><![CDATA[//><!--
    <?php print $mcti_js_countdown; ?>
    //--><!]]>
  </script>
</body>
</html>


