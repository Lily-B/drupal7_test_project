<?php
/**
 * Add new row in pets_owners_storage table
 * @param $entry
 * @return \DatabaseStatementInterface|int|null
 */
function add_new_pets_owner_in_db($entry) {
  $return_value = NULL;
  try {
    $return_value = db_insert('pets_owners_storage')
      ->fields($entry)
      ->execute();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_insert failed. Message = %message, query= %query',
      array(
        '%message' => $e->getMessage(),
        '%query' => $e->query_string
      )), 'error');
  }
  return $return_value;
}

/**
 * Check if the person with this e-mail already exists in pets_owners_storage table
 * @param $email
 * @return null
 */
function email_exists_in_db($email) {
  $row_exists = NULL;
  try {
    $row_exists = db_select('pets_owners_storage', 's')
      ->fields('s', array('first_name'))
      ->condition('s.email', $email)
      ->execute()
      ->fetchField();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_select failed. Message = %message, query= %query',
      array(
        '%message' => $e->getMessage(),
        '%query' => $e->query_string
      )), 'error');
  }
  return $row_exists;
}

/**
 * Select all pets owners from db and Return the result in object format
 * @param array $entry
 * @return mixed
 */
function all_pets_owners_in_db() {
  $select = db_select('pets_owners_storage', 's')
    ->extend('PagerDefault')
    ->fields('s')
    ->limit(5)
    ->orderBy('s.first_name')
    ->execute();

  return $select->fetchAll();
}

/**
 * Find row from table pets_owners_storage by id
 * @param $id
 * @return mixed
 */
function find_pet_owner_by_id($id) {
  $rows = NULL;
  try {
    $rows = db_select('pets_owners_storage', 's')
      ->fields('s')
      ->condition('s.id', $id)
      ->execute()
      ->fetchObject();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_select failed. Message = %message, query= %query',
      array(
        '%message' => $e->getMessage(),
        '%query' => $e->query_string
      )), 'error');
  }
  return $rows;
}

/**
 * Edits row in pets_owners_storage table by id
 * @param $id
 * @param $entry
 * @return bool
 */
function edit_pets_owner_in_db($id, $entry) {
  try {
    db_update('pets_owners_storage')
      ->fields($entry)
      ->condition('id', $id)
      ->execute();
    return TRUE;
  }
  catch (Exception $e) {
    drupal_set_message(t('db_update failed. Message = %message, query= %query',
      array(
        '%message' => $e->getMessage(),
        '%query' => $e->query_string
      )), 'error');
    return FALSE;
  }
}

/**
 * Delete row from table pets_owners_storage by id
 * @param $id
 * @return mixed
 */
function delete_pet_owner_by_id($id) {
  try {
    db_delete('pets_owners_storage')
      ->condition('id', $id)
      ->execute();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_select failed. Message = %message, query= %query',
      array(
        '%message' => $e->getMessage(),
        '%query' => $e->query_string
      )), 'error');
    return FALSE;
  }
  return TRUE;
}

/**
 * Check does any other user with same email exists
 * @param $owner_id
 * @param $owner_email
 * @return bool
 */
function is_owners_email_unique($owner_id, $owner_email) {
  $same_emails = db_select('pets_owners_storage', 's')
    ->fields('s')
    ->condition('s.id', $owner_id, '<>')
    ->condition('s.email', $owner_email, '=')
    ->execute()
    ->fetchAll();
  return (count($same_emails) == 0);
}

/**
 * function for select content in pets owners form
 * @param $voc
 * @return mixed
 */
function get_all_terms_of_vocab($voc_name) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($voc_name);
  $terms = taxonomy_get_tree($vocabulary->vid);
  foreach ($terms as $data) {
    $output[$data->tid] = $data->name;
  }
  return $output;
}

/**
 * Convert date from form date field to timestamp
 * @param $form_date_fields
 * @return int
 */
function forms_date_to_timestamp($form_date_fields) {
  $string_date = "{$form_date_fields['year']}-{$form_date_fields['month']}-{$form_date_fields['day']}";
  $timezone = NULL;
  $date_time = new DateTime($string_date, $timezone);
  $timestamp = $date_time->getTimestamp();
  return $timestamp;
}

/**
 * Check if this first_name&last_name&birthday_timestamp already exist in database
 * @param $owner_id
 * @param $owner_f_name
 * @param $owner_l_name
 * @param $owner_birth
 * @return bool
 */
function are_owner_names_and_birth_unique($owner_id, $owner_f_name, $owner_l_name, $owner_birth) {

  $same_rows = db_select('pets_owners_storage', 's')
    ->fields('s');
  if (isset($owner_id)) {
    $same_rows = $same_rows->condition('s.id', $owner_id, '<>');
  };
  $same_rows = $same_rows->condition('s.first_name', $owner_f_name, '=')
    ->condition('s.last_name', $owner_l_name, '=')
    ->condition('s.birthday_timestamp', $owner_birth, '=')
    ->execute()
    ->fetchAll();
return (count($same_rows) == 0);
}
