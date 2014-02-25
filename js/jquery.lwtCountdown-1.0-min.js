/**
 * jQuery Countdown plugin v1.0
 * http://www.littlewebthings.com/projects/countdown/
 *
 * Copyright 2010, Vassilis Dourdounis
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

jQuery.noConflict();(function(a){a(function(){a.fn.countDown=function(b){config={};a.extend(config,b);diffSecs=this.setCountDown(config);if(config.onComplete){a.data(a(this)[0],"callback",config.onComplete);}if(config.omitWeeks){a.data(a(this)[0],"omitWeeks",config.omitWeeks);}a("#"+a(this).attr("id")+" .digit").html('<div class="top"></div><div class="bottom"></div>');a(this).doCountDown(a(this).attr("id"),diffSecs,500);return this;};a.fn.stopCountDown=function(){clearTimeout(a.data(this[0],"timer"));};a.fn.startCountDown=function(){this.doCountDown(a(this).attr("id"),a.data(this[0],"diffSecs"),500);};a.fn.setCountDown=function(b){var d=new Date();if(b.targetDate){d=new Date(b.targetDate.month+"/"+b.targetDate.day+"/"+b.targetDate.year+" "+b.targetDate.hour+":"+b.targetDate.min+":"+b.targetDate.sec+" "+b.targetDate.utc);}else{if(b.targetOffset){d.setFullYear(b.targetOffset.year+d.getFullYear());d.setMonth(b.targetOffset.month+d.getMonth());d.setDate(b.targetOffset.day+d.getDate());d.setHours(b.targetOffset.hour+d.getHours());d.setMinutes(b.targetOffset.min+d.getMinutes());d.setSeconds(b.targetOffset.sec+d.getSeconds());}}var c=new Date();diffSecs=Math.floor((d.valueOf()-c.valueOf())/1000);a.data(this[0],"diffSecs",diffSecs);return diffSecs;};a.fn.doCountDown=function(d,b,c){$this=a("#"+d);if(b<=0){b=0;if(a.data($this[0],"timer")){clearTimeout(a.data($this[0],"timer"));}}secs=b%60;mins=Math.floor(b/60)%60;hours=Math.floor(b/60/60)%24;if(a.data($this[0],"omitWeeks")==true){days=Math.floor(b/60/60/24);weeks=Math.floor(b/60/60/24/7);}else{days=Math.floor(b/60/60/24)%7;weeks=Math.floor(b/60/60/24/7);}$this.dashChangeTo(d,"seconds_dash",secs,c?c:800);$this.dashChangeTo(d,"minutes_dash",mins,c?c:1200);$this.dashChangeTo(d,"hours_dash",hours,c?c:1200);$this.dashChangeTo(d,"days_dash",days,c?c:1200);$this.dashChangeTo(d,"weeks_dash",weeks,c?c:1200);a.data($this[0],"diffSecs",b);if(b>0){e=$this;t=setTimeout(function(){e.doCountDown(d,b-1);},1000);a.data(e[0],"timer",t);}else{if(cb=a.data($this[0],"callback")){a.data($this[0],"callback")();}}};a.fn.dashChangeTo=function(j,g,h,c){$this=a("#"+j);for(var b=($this.find("."+g+" .digit").length-1);b>=0;b--){var f=h%10;h=(h-f)/10;$this.digitChangeTo("#"+$this.attr("id")+" ."+g+" .digit:eq("+b+")",f,c);}};a.fn.digitChangeTo=function(d,c,b){if(!b){b=800;}if(a(d+" div.top").html()!=c+""){a(d+" div.top").css({display:"none"});a(d+" div.top").html((c?c:"0")).slideDown(b);a(d+" div.bottom").animate({height:""},b,function(){a(d+" div.bottom").html(a(d+" div.top").html());a(d+" div.bottom").css({display:"block",height:""});a(d+" div.top").hide().slideUp(10);});}};});})(jQuery);