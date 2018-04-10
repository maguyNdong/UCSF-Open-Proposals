<?php
/**
 * @file
 * Variable module integration.
 */

/**
 * Implements hook_variable_info().
 */
function reroute_email_variable_info() {
  $variable = array();

  $variable[REROUTE_EMAIL_ENABLE] = array(
    'title' => t('Enable rerouting'),
    'description' => t('Check this box if you want to enable email rerouting. Uncheck to disable rerouting.'),
    'type' => 'boolean',
    'default' => 0,
    'group' => 'reroute_email',
  );

  $variable[REROUTE_EMAIL_TO] = array(
    'title' => t('Destination email addresses'),
    'description' => t('Provide a space, comma, semicolon, or newline-delimited list of email addresses to reroute email messages to.'),
    'type' => 'text',
    'default' => REROUTE_EMAIL_DEFAULT_ADDRESS,
    'group' => 'reroute_email',
  );

  $variable[REROUTE_EMAIL_WHITELIST] = array(
    'title' => t('Email address whitelist'),
    'description' => t('Provide a space, comma, semicolon, or newline-delimited list of email addresses to permit delivery to.'),
    'type' => 'text',
    'default' => REROUTE_EMAIL_DEFAULT_ADDRESS,
    'group' => 'reroute_email',
  );

  $variable[REROUTE_EMAIL_DOMAIN_WHITELIST] = array(
    'title' => t('Domain whitelist'),
    'description' => t('Provide a space, comma, or semicolon-delimited list of domains to permit delivery to.'),
    'type' => 'string',
    'default' => '',
    'group' => 'reroute_email',
  );

  $variable[REROUTE_EMAIL_ENABLE_MESSAGE] = array(
    'title' => t('Show rerouting description in mail body'),
    'description' => t('Check this box if you want a message to be inserted into the email body when the mail is being rerouted. Otherwise, SMTP headers will be used to describe the rerouting. If sending rich-text email, leave this unchecked so that the body of the email will not be disturbed.'),
    'type' => 'boolean',
    'default' => 1,
    'group' => 'reroute_email',
  );

  return $variable;
}

/**
 * Implements hook_variable_group_info().
 */
function reroute_email_variable_group_info() {
  $groups['reroute_email'] = array(
    'title' => t('Reroute Email'),
    'description' => t('Reroute email configuration settings'),
    'access' => 'administer reroute email',
    'path' => array('admin/config/development/reroute_email'),
  );
  return $groups;
}