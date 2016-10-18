<?php
/**
 * Process every item in batch
 * @param $rows
 * @param $new_name
 * @param $context
 */
function name_changer_process_row($rows, $new_name, &$context) {

  $limit = 50;

  if (empty($context['sandbox']['progress'])) {

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($rows);
  }

  if (empty($context['sandbox']['items'])) {
    $context['sandbox']['items'] = $rows;
  }

  $counter = 0;
  if (!empty($context['sandbox']['items'])) {

    if ($context['sandbox']['progress'] != 0) {
      array_splice($context['sandbox']['items'], 0, $limit);
    }

    foreach ($context['sandbox']['items'] as $id) {
      if ($counter != $limit) {

        change_pet_owners_name($id, $new_name);

        $counter++;
        $context['sandbox']['progress']++;

        $context['message'] = t('Now processing node %progress of %count', array(
          '%progress' => $context['sandbox']['progress'],
          '%count' => $context['sandbox']['max']
        ));
        $context['results']['processed'] = $context['sandbox']['progress'];
      }
    }
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finish callback for Batch
 */
function name_changer_finished_callback($success, $results, $operations) {
  if ($success) {
    if (isset($results['processed'])) {
      $message = format_plural($results['processed'], 'One node processed.', '@count nodes processed.');
    }
    else {
      $message = 'There are no users in database with this name.';
    }
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}

/**
 * Changes first_name in pets_owners_storage by id
 * @param $id
 * @param $new_name
 * @return bool
 */
function change_pet_owners_name($id, $new_name) {
  try {
    db_update('pets_owners_storage')
      ->fields(['first_name' => $new_name])
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