<?php

/**
 * @file
 * Views integration for Entity Reference.
 */

/**
 * Implements hook_field_views_data().
 */
function entityreference_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $entity_info = entity_get_info($field['settings']['target_type']);
  foreach ($data as $table_name => $table_data) {
    if (isset($entity_info['base table'])) {
      $entity = $entity_info['label'];
      if ($entity == t('Node')) {
        $entity = t('Content');
      }

      $field_name = $field['field_name'] . '_target_id';
      $parameters = array('@entity' => $entity, '!field_name' => $field['field_name']);
      $data[$table_name][$field_name]['relationship'] = array(
        'handler' => 'views_handler_relationship',
        'base' => $entity_info['base table'],
        'base field' => $entity_info['entity keys']['id'],
        'label' => t('@entity entity referenced from !field_name', $parameters),
        'group' => t('Entity Reference'),
        'title' => t('Referenced Entity'),
        'help' => t('A bridge to the @entity entity that is referenced via !field_name', $parameters),
      );
    }
  }

  // Invoke the behaviors to allow them to change the properties.
  foreach (entityreference_get_behavior_handlers($field) as $handler) {
    $handler->views_data_alter($data, $field);
  }

  return $data;
}

/**
 * Options callback for Views handler views_handler_filter_in_operator.
 */
function entityreference_views_handler_options_list($field_name) {
  $field = field_info_field($field_name);
  return entityreference_options_list($field);
}

/**
 * Implements hook_field_views_data_views_data_alter().
 *
 * Views integration to provide reverse relationships on entityreference fields.
 */
function entityreference_field_views_data_views_data_alter(&$data, $field) {
  foreach ($field['bundles'] as $entity_type => $bundles) {
    $target_entity_info = entity_get_info($field['settings']['target_type']);
    if (isset($target_entity_info['base table'])) {
      $entity_info = entity_get_info($entity_type);
      $entity = $entity_info['label'];
      if ($entity == t('Node')) {
        $entity = t('Content');
      }
      $target_entity = $target_entity_info['label'];
      if ($target_entity == t('Node')) {
        $target_entity = t('Content');
      }
      if (empty($data[$target_entity_info['base table']]['table']['base']['field'])) {
        $target_left_field = $target_entity_info['entity keys']['id'];
      }
      else {
        $target_left_field = $data[$target_entity_info['base table']]['table']['base']['field'];
      }

      $pseudo_field_name = 'reverse_' . $field['field_name'] . '_' . $entity_type;
      $replacements = array('@entity' => $entity, '@target_entity' => $target_entity, '!field_name' => $field['field_name']);
      $data[$target_entity_info['base table']][$pseudo_field_name]['relationship'] = array(
        'handler' => 'entityreference_views_handler_relationship_entity_reverse',
        'field_name' => $field['field_name'],
        'field table' => _field_sql_storage_tablename($field),
        'field field' => $field['field_name'] . '_target_id',
        'base' => $entity_info['base table'],
        'base field' => $entity_info['entity keys']['id'],
        'label' => t('@entity referencing @target_entity from !field_name', $replacements),
        'group' => t('Entity Reference'),
        'title' => t('Referencing entity'),
        'help' => t('A bridge to the @entity entity that is referencing @target_entity via !field_name', $replacements),
        'join_extra' => array(
          0 => array(
            'field' => 'entity_type',
            'value' => $entity_type,
          ),
          1 => array(
            'field' => 'deleted',
            'value' => 0,
            'numeric' => TRUE,
          ),
        ),
        'target left field' => $target_left_field,
      );
    }
  }
}

/**
 * Implements hook_views_plugins().
 */
function entityreference_views_plugins() {
  $plugins = array(
    'display' => array(
      'entityreference' => array(
        'title' => t('Entity Reference'),
        'admin' => t('Entity Reference Source'),
        'help' => 'Selects referenceable entities for an entity reference field',
        'handler' => 'entityreference_plugin_display',
        'uses hook menu' => FALSE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        // Custom property, used with views_get_applicable_views() to retrieve
        // all views with a 'Entity Reference' display.
        'entityreference display' => TRUE,
      ),
    ),
    'style' => array(
      'entityreference_style' => array(
        'title' => t('Entity Reference list'),
        'help' => 'Returns results as a PHP array of labels and rendered rows.',
        'handler' => 'entityreference_plugin_style',
        'theme' => 'views_view_unformatted',
        'uses row plugin' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'entityreference',
        'even empty' => TRUE,
      ),
    ),
    'row' => array(
      'entityreference_fields' => array(
        'title' => t('Inline fields'),
        'help' => t('Displays the fields with an optional template.'),
        'handler' => 'entityreference_plugin_row_fields',
        'theme' => 'views_view_fields',
        'theme path' => drupal_get_path('module', 'views') . '/theme',
        'theme file' => 'theme.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'entityreference',
      ),
    ),
  );
  return $plugins;
}

/**
 * A relationship handlers which reverse entity references.
 *  Altered to allow for support of entities that are not Views base tables.
 *  (e.g. taxonomy_vocabulary)
 */
class entityreference_views_handler_relationship_entity_reverse extends views_handler_relationship_entity_reverse {
  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    $this->ensure_my_table();
    // First, relate our base table to the current base table to the
    // field, using the base table's id field to the field's column.
    if (isset($this->definition['target left field'])) {
      $left_field = $this->definition['target left field'];
    }
    else {
      $views_data = views_fetch_data($this->table);
      $left_field = $views_data['table']['base']['field'];
    }

    $first = array(
      'left_table' => $this->table_alias,
      'left_field' => $left_field,
      'table' => $this->definition['field table'],
      'field' => $this->definition['field field'],
    );
    if (!empty($this->options['required'])) {
      $first['type'] = 'INNER';
    }

    if (!empty($this->definition['join_extra'])) {
      $first['extra'] = $this->definition['join_extra'];
    }

    if (!empty($this->definition['join_handler']) && class_exists($this->definition['join_handler'])) {
      $first_join = new $this->definition['join_handler'];
    }
    else {
      $first_join = new views_join();
    }
    $first_join->definition = $first;
    $first_join->construct();
    $first_join->adjusted = TRUE;

    $this->first_alias = $this->query->add_table($this->definition['field table'], $this->relationship, $first_join);

    // Second, relate the field table to the entity specified using
    // the entity id on the field table and the entity's id field.
    $second = array(
      'left_table' => $this->first_alias,
      'left_field' => 'entity_id',
      'table' => $this->definition['base'],
      'field' => $this->definition['base field'],
    );

    if (!empty($this->options['required'])) {
      $second['type'] = 'INNER';
    }

    if (!empty($this->definition['join_handler']) && class_exists($this->definition['join_handler'])) {
      $second_join = new $this->definition['join_handler'];
    }
    else {
      $second_join = new views_join();
    }
    $second_join->definition = $second;
    $second_join->construct();
    $second_join->adjusted = TRUE;

    // use a short alias for this:
    $alias = $this->definition['field_name'] . '_' . $this->table;

    $this->alias = $this->query->add_relationship($alias, $second_join, $this->definition['base'], $this->relationship);
  }
}
