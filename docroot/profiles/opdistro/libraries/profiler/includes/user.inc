<?php
/**
 * User module integration.
 */

/**
 * Implementation of hook_profiler_components() on behalf of user.
 */
function user_profiler_components() {
  return array(
    'users' => array(
      'callback' => 'profiler_install_users',
      'weight' => -10,
    ),
    'roles' => array(
      'callback' => 'profiler_install_roles',
      'weight' => -15,
    ),
  );
}

/**
 * Component install callback for 'users'.
 */
function profiler_install_users($users) {
  foreach (array_filter($users) as $array) {
    $roles = isset($array['roles']) ? $array['roles'] : '';
    // Set the roles.
    $array['roles'] = array();
    $roles = explode(',', $roles);
    foreach ($roles as $name) {
      if ($rid = _profiler_role_id_from_name($name)) {
        $array['roles'][$rid] = $name;
      }
    }

    // Use random password.
    $array['pass'] = empty($array['pass']) ? user_password() : $array['pass'];

    // Load and update the account or create a new one.
    $account = isset($array['uid']) ? user_load($array['uid']) : user_load_by_name($array['name']);
    $account = $account ? $account : new stdClass();
    $account = user_save($account, $array);
  }
}

/**
 * Component install callback for 'roles'.
 */
function profiler_install_roles($roles) {
  foreach (array_filter($roles) as $role_data) {
    // Create the role object.
    $role = new stdClass();

    // Allow simple strings and arrays with name and weight.
    if (is_array($role_data)){
      $role->name = $role_data['name'];
      if (isset($role_data['weight'])) {
        $role->weight = $role_data['weight'];
      }
    }
    else {
      $role->name = $role_data;
    }

    // Save the role.
    user_role_save($role);
  }
}
