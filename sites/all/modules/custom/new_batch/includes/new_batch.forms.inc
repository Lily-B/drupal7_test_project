<?php
module_load_include('inc', 'new_batch', 'includes/custom_fapi_validation_rules');
/**
 * Custom subscription form.
 * @param $form
 * @param $form_state
 * @return mixed
 */
function new_batch_change_name_form($form, &$form_state) {

  $form['old_first_name'] = [
    '#title' => t('Old Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => [
      'placeholder' => t('Old Name '),
    ],
    '#size' => 20,
    '#maxlength' => 20,
    '#rules' => [
      'alpha_dash',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      ],
    ],
  ];

  $form['new_first_name'] = [
    '#title' => t('New Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => [
      'placeholder' => t('New Name '),
    ],
    '#size' => 20,
    '#maxlength' => 20,
    '#rules' => [
      'alpha_dash',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      ],
    ],
  ];

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Change!'),
  );
  return $form;
}

/**
 * Implement hook_form_submit().
 * @param $form
 * @param $form_state
 */
function new_batch_change_name_form_submit($form, &$form_state) {

  $old_name = trim($form_state['values']['old_first_name']);
  $new_name = trim($form_state['values']['new_first_name']);
  $ids = find_pets_owners_ids_with_name($old_name);

  $batch = array(
    'title' => t('Row processing'),
    'operations' => array(
      array('name_changer_process_row', array($ids, $new_name)),
    ),
    'finished' => 'name_changer_finished_callback',
    'file' => drupal_get_path('module', 'new_batch') . '/includes/new_batch.batch.inc',
  );

  batch_set($batch);
  batch_process();

  drupal_set_message(t('Success!'));
}

/**
 * Select all pets owners with $old_name from db
 * @param $old_name
 * @return array of ids
 */
function find_pets_owners_ids_with_name($old_name) {

  $rows = [];
  try {
    $rows = db_select('pets_owners_storage', 's')
      ->fields('s', ['id'])
      ->condition('s.first_name', $old_name)
      ->execute();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_select failed. Message = %message, query= %query',
      array(
        '%message' => $e->getMessage(),
        '%query' => $e->query_string
      )), 'error');
  }
  $output = [];
  foreach ($rows as $user) {
    $output[] = $user->id;
  }
  return ($output);
}