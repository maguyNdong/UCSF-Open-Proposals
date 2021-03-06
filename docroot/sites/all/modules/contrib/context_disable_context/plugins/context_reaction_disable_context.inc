<?php
// $Id$

/**
 * Expose themes as context reactions.
 */
class context_reaction_disable_context extends context_reaction {
  /**
   * Allow admins to provide a section title, section subtitle and section class.
   */
  function options_form($context) {
    $defaults = $this->fetch_from_context($context);
    $values = context_context_list();
    // Exclude the current context from the options.
    if (isset($values[$context->name])) {
      unset($values[$context->name]);
    }
    ksort($values);

    $form = array();
    $form['disabled'] = array(
      '#title' => t('Contexts to disable'),
      '#decription' => t('Select the contexts that should be disabled'),
      '#type' => 'checkboxes',
      '#multiple' => TRUE,
      '#options' => $values,
      '#default_value' => isset($defaults['disabled']) ? $defaults['disabled'] : array() ,
    );
    
    return $form;
  }

  /**
   * Options form submit handler.
   */
  function options_form_submit($values) {
    $values['disabled'] = array_filter($values['disabled']);
    return $values;
  }

  function execute() {
    $contexts = $this->get_contexts();
    $processed = array();
    
    $setcontexts = context_get('context');
    foreach ($contexts as $context) {
      $values = $this->fetch_from_context($context);
      
      foreach ($values['disabled'] as $disable) {
        if (isset($setcontexts[$disable]) && !in_array($disable, $processed)) {
          unset($setcontexts[$disable]);
        }
      }
      
      // Add the current context to $processed so it is not removed by other contexts
      $processed[] = $context->name;
    }
    context_set('context', $setcontexts);
  }
}
