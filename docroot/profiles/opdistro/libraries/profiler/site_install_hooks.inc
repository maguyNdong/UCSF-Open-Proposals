<?php
/**
 * @file
 *  Site Install Hooks API functionality.
 */

/**
 * Pseudo-implementation of hook_install_tasks_alter().
 *
 * Called by profiler_install_tasks_alter().
 */
function _profiler_site_install_hooks_tasks_alter(&$tasks, $install_state) {
  $pre_install_task = array(
    'display_name' => st('Start installation'),
    'display'      => TRUE,
    'type'         => 'normal',
  );

  // Insert a pre-install task right before install_profile_modules.
  _profiler_array_insert_before(
    $tasks,
    'install_profile_modules',
    'profiler_site_install_hooks_invoke_pre_install',
    $pre_install_task);

  $post_install_task = array(
    'display_name' => st('Finalize installation'),
    'display'      => TRUE,
    'type'         => 'normal',
  );

  // Insert a post-install task right before install_finished.
  _profiler_array_insert_before(
    $tasks,
    'install_finished',
    'profiler_site_install_hooks_invoke_post_install',
    $post_install_task);
}

/**
 * Install callback that invokes hook_site_pre_install() on all modules.
 *
 * This hook is invoked immediately before install_profile_modules() in Drupal
 * core.
 *
 * @param array $install_state
 *   A reference to the site installation state.
 */
function profiler_site_install_hooks_invoke_pre_install(&$install_state) {
  $profile_name = $install_state['parameters']['profile'];

  _profiler_site_install_hooks_invoke_install_hook_on_all_modules('site_pre_install', $profile_name);
}

/**
 * Install callback that invokes hook_site_pre_install() on all modules.
 *
 * This hook is invoked immediately before install_finished() in Drupal
 * core.
 *
 * @param array $install_state
 *   A reference to the site installation state.
 */
function profiler_site_install_hooks_invoke_post_install(&$install_state) {
  $profile_name = $install_state['parameters']['profile'];

  _profiler_site_install_hooks_invoke_install_hook_on_all_modules('site_post_install', $profile_name);
}

/**
 * Invokes the specified hook on all installed and enabled modules.
 *
 * @param string $hook_name
 *   The name of the hook to invoke.
 *
 * @param string $profile_name
 *   The machine name of the installation profile.
 */
function _profiler_site_install_hooks_invoke_install_hook_on_all_modules($hook_name, $profile_name) {
  /* Always include the installation profile in the list so its pre- and
   * post-install hooks can be invoked.
   */
  $modules = module_list() + array($profile_name => $profile_name);

  watchdog(
    'profiler',
    'Invoking %hook on all modules',
    array('%hook' => $hook_name),
    WATCHDOG_DEBUG);

  $implementations = array();

  foreach ($modules as $module_name) {
    /* Load .install file for the module, in case the pre-/post-install hook is
     * located there.
     */
    module_load_install($module_name);

    if (module_hook($module_name, $hook_name)) {
      /* FALSE takes the place of the group value. It's counter-intuitive, but
       * that's what core uses...
       */
      $implementations[$module_name] = FALSE;
    }
  }

  // Give modules a chance to re-order their pre- and post-install hooks
  drupal_alter('module_implements', $implementations, $hook_name);

  foreach ($implementations as $module_name => $group) {
    watchdog(
      'profiler',
      'Invoking %hook on %module',
      array(
        '%hook' => $hook_name,
        '%module' => $module_name),
      WATCHDOG_DEBUG);

    module_invoke($module_name, $hook_name);
  }
}

/**
 * Inserts the provided key and value pair before the specified key in the
 * provided array.
 *
 * For example, consider this array:
 * <pre>
 *   array(
 *     'a' => 'apple',
 *     'c' => 'carrot',
 *   );
 * </pre>
 *
 * Now, assume we call this method like so:
 * _profiler_array_insert_before($array, 'c', 'b', 'banana')
 *
 * The array would now contain:
 * <pre>
 *   array(
 *     'a' => 'apple',
 *     'b' => 'banana',
 *     'c' => 'carrot',
 *   );
 * </pre>
 *
 * If $following_key is not a key in $array, the array is not modified.
 *
 * @param array $array
 *   A reference to the associative array that is to be modified.
 *
 * @param mixed $following_key
 *   The key in $array before which the new key and value will be inserted.
 *
 * @param mixed $new_key
 *   The new key to insert before $following_key in $array.
 *
 * @param mixed $new_value
 *   The value to associate with $new_key in $array.
 */
function _profiler_array_insert_before(array &$array, $following_key, $new_key, $new_value) {
  $new_array = array();

  foreach ($array as $current_key => $current_value) {
    // Insert the new element before putting the target element in.
    if ($current_key === $following_key) {
      $new_array[$new_key] = $new_value;
    }

    $new_array[$current_key] = $current_value;
  }

  // Replace the contents of the passed-in array with the new array
  $array = $new_array;
}