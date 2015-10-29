<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 * least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 * or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 * when linking to the front page. This includes the language domain or
 * prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 * in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 * in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 * site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 * the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 * modules, intended to be displayed in front of the main title tag that
 * appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 * modules, intended to be displayed after the main title tag that appears in
 * the template.
 * - $messages: HTML for status and error messages. Should be displayed
 * prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 * (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 * menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 * associated with the page, and the node ID is the second argument
 * in the page's path (e.g. node/12345 and node/12345/revisions, but not
 * comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<header id="head" role="banner" class="container">

    <div id="ucsf-links">
      <?php if (!ctsi_region_empty($page['ucsf_links'])): ?>
        <?php print render($page['ucsf_links']); ?>
      <?php endif; ?>
    </div>

  <hgroup class="sixteen columns alpha omega">

    <div id="brand">
      <?php if (!ctsi_region_empty($page['brand'])): ?>
        <?php print render($page['brand']); ?>
      <?php endif; ?>
    </div>

    <div id="logo">
      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print $site_name; ?>
           <?php print t('&nbsp;» Home Page'); ?>">
        <img id="logo-img" src="<?php print $logo; ?>" alt="<?php print $site_name; ?>
        <?php print t(' » Home Page'); ?>"/></a>
      <?php endif; ?>
    </div>

    <div id="site-title-wrapper">
      <h1 id="site-title">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
       <?php print $site_name; ?>
        </a>
      </h1>
      <?php if ($site_slogan): ?>
        <div class="site-slogan"><?php print $site_slogan; ?></div><!--site slogan-->
      <?php endif; ?>
    </div>

    <div id="top-links">
      <?php if (!ctsi_region_empty($page['top_links'])): ?>
        <?php print render($page['top_links']); ?>
      <?php endif; ?>
    </div>

  </hgroup>

</header>

<div id="menu-wrapper" class="container">
  <nav id="main-menu" role="navigation" class="sixteen columns alpha omega">
    <div class="menu-navigation-container">
      <!-- Theme native drop downs and mobile menu-->
      <div id="nav-wrap">
        <?php if ($primary_nav): ?>
          <div id="menu-icon"></div>
          <?php print render($primary_nav); ?>
        <?php endif; ?>
        <!-- region to place search form inside navbar -->
        <?php if (!ctsi_region_empty($page['main_menu'])): ?>
          <?php print render($page['main_menu']); ?>
        <?php endif; ?>
      </div>
    </div>
  </nav>
</div>
<!-- end main-menu -->

<div class="container" id="content-wrapper">

  <?php if (!ctsi_region_empty($page['hero_first'])): ?>
    <!--above breadcrumbs-->
    <div id="hero-first" class="sixteen columns">
      <?php print render($page['hero_first']); ?>
    </div>
  <?php endif; ?>

  <?php if ($breadcrumb): ?>
    <div id="breadcrumbs">
      <?php print $breadcrumb; ?>
    </div>
  <?php endif; ?>

    <?php if (!ctsi_region_empty($page['hero_second'])): ?>
    <!--below breadcrumbs-->
    <div id="hero-second" class="sixteen columns">
      <?php print render($page['hero_second']); ?>
    </div>
    <?php endif; ?>

  <?php
  // Define and divide the preface page regions.
  if (!ctsi_region_empty($page['preface_first']) || !ctsi_region_empty($page['preface_second']) ||
  !ctsi_region_empty($page['preface_third'])):
  ?>

  <div id="preface-wrapper">

  <?php
  $bottom = (!ctsi_region_empty($page['preface_first']) + !ctsi_region_empty($page['preface_second']) +
    !ctsi_region_empty($page['preface_third']));

  switch ($bottom) :

    case 1:
      $preface_wid = "sixteen columns";
      break;

    case 2:
      $preface_wid = "eight columns";
      break;

    case 3:
      $preface_wid = "one-third column";
      break;

  endswitch;
  ?>

  <?php if (!ctsi_region_empty($page['preface_first'])): ?>
  <div class="<?php print $preface_wid; ?> preface-area">
    <?php print render($page['preface_first']); ?>
  </div>
  <?php endif; ?>

  <?php if (!ctsi_region_empty($page['preface_second'])): ?>
  <div class="<?php print $preface_wid; ?> preface-area">
    <?php print render($page['preface_second']); ?>
  </div>
  <?php endif; ?>

  <?php if (!ctsi_region_empty($page['preface_third'])): ?>
  <div class="<?php print $preface_wid; ?> preface-area">
    <?php print render($page['preface_third']); ?>
  </div>
  <?php endif; ?>
  </div>
  <?php endif; ?>

  <?php if (!ctsi_region_empty($page['sidebar_first'])): ?>
    <?php $contentwid = "eleven"; ?>
  <?php else: ?>
    <?php $contentwid = "sixteen"; ?>
  <?php endif; ?>

  <div id="content" class="<?php print $contentwid; ?> columns">
    <?php print $messages; ?>
    <section id="post-content" role="main" class="<?php print $classes; ?>" >

      <?php if (!ctsi_region_empty($page['content_top'])): ?>
        <div id="content_top"><?php print render($page['content_top']); ?></div>
      <?php endif; ?>

      <?php if (!empty($section_title)): ?><h2 class="title"><?php print $section_title; ?></h2>
      <?php endif; ?>
      <?php if (!empty($section_subtitle)): ?><h3 class="title"><?php print $section_subtitle; ?></h3>
      <?php endif; ?>

      <?php print render($title_prefix); ?>
      <?php if ($title): ?><h1 class="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if (!empty($tabs['#primary'])): ?>
        <div class="tabs-wrapper"><?php print render($tabs); ?></div>
      <?php endif; ?>

      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php if (!ctsi_region_empty($page['content_after_title'])): ?>
        <div id="content_after_title"><?php print render($page['content_after_title']); ?></div>
      <?php endif; ?>
      <?php print render($page['content']); ?>

    </section>
    <!-- /#main -->
  </div>

    <?php if (!ctsi_region_empty($page['sidebar_first'])): ?>
    <aside id="sidebar-first" role="complementary" class="sidebar five columns">
    <?php print render($page['sidebar_first']); ?>
    </aside><!-- /#sidebar-first -->
<?php endif; ?>

</div>

<div id="acknowledgement-wrapper" class="container">

  <?php if (!ctsi_region_empty($page['acknowledgement'])): ?>
    <div id="acknowledgement" class="sixteen columns">
      <?php print render($page['acknowledgement']); ?>
    </div>
  <?php endif; ?>

</div>

<footer id="colophon" class="container">

  <?php
  // Define and divide the footer page regions.
  if (!ctsi_region_empty($page['footer_first']) || !ctsi_region_empty($page['footer_second']) ||
          !ctsi_region_empty($page['footer_third'])):

    $bottom = (!ctsi_region_empty($page['footer_first']) + !ctsi_region_empty($page['footer_second']) + !ctsi_region_empty($page['footer_third']));

    switch ($bottom) :

      case 1:
        $footer_wid = "sixteen columns";
        break;

      case 2:
        $footer_wid = "eight columns";
        break;

      case 3:
        $footer_wid = "one-third column";
        break;

    endswitch;
    ?>

      <?php if (!ctsi_region_empty($page['footer_first'])): ?>
      <div class="<?php print $footer_wid; ?> footer-area">
      <?php print render($page['footer_first']); ?>
      </div>
      <?php endif; ?>
      <?php if (!ctsi_region_empty($page['footer_second'])): ?>
      <div class="<?php print $footer_wid; ?> footer-area">
      <?php print render($page['footer_second']); ?>
      </div>
      <?php endif; ?>
      <?php if (!ctsi_region_empty($page['footer_third'])): ?>
      <div class="<?php print $footer_wid; ?> footer-area">
      <?php print render($page['footer_third']); ?>
      </div>
      <?php endif; ?>

<?php endif; ?>

<?php if (empty($GLOBALS['nocetrk'])) : ?>
<script type="text/javascript">
//CrazyEgg click tracking
setTimeout(function(){var a=document.createElement("script");
var b=document.getElementsByTagName("script")[0];
a.src=document.location.protocol+"//dnn506yrbagrg.cloudfront.net/pages/scripts/0010/2559.js?"+Math.floor(new Date().getTime()/3600000);
a.async=true;a.type="text/javascript";b.parentNode.insertBefore(a,b)}, 1);
</script>
<?php endif; ?>

</footer>
