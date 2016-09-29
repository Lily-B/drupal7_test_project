<?php

function add_new_pets_owner($entry) {
  $return_value = NULL;
  try {
    $return_value =db_insert('pets_owners_storage')
      ->fields($entry)
      ->execute();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_insert failed. Message = %message, query= %query',
      array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
  }
  return $return_value;
}

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
      array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
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
      ->fields('s')
      ->execute();

  return $select->fetchAll();
}
