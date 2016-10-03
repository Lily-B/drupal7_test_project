<?php

///**
// * Callback function for pets_owners_storage_form
// * @param string $id
// * @return array|mixed
// */
//function pets_owners_storage_form_callback($id = 'all') {
////  $new = TRUE;
////  $owner = null;
////  if(isset($id)){
////    $owner = find_pet_owner_by_id($id);
////    $new = FALSE;
////  }
//  if (!isset($id)) {
//    $id = NULL;
//  }
//  return drupal_get_form('pets_owners_storage_form');
//}

/**
 * Confirm page for delete with 2 links
 * @param string $id
 * @return string
 */
function pets_owners_storage_confirm_callback($id = 'all') {
  $owner = find_pet_owner_by_id($id);
  $output = '<h2>Are you sure, you want to delete '
    . htmlentities($owner->first_name) . ' '
    . htmlentities($owner->last_name) . '?</h2>';
  $output .= l(t('Delete'), 'pets_owners_storage/delete_owner/'
    . $owner->id, array('attributes' => array('class' => 'delete-link')));
  $output .= '&nbsp;&nbsp;&nbsp;';
  $output .= l(t('Cancel'), 'pets_owners_storage/pets_owners_page',
    array('attributes' => array('class' => 'cancel-link')));
  return $output;
}

function pets_owners_storage_delete_callback($id = 'all') {
  delete_pet_owner_by_id($id);
  drupal_goto('pets_owners_storage/pets_owners_page');
}

/**
 * Callback function for pets_owners_storage_edit_form
 * @param string $id
 * @return array|mixed
 */
function pets_owners_storage_edit_form_callback($id = 'all') {
  $owner = find_pet_owner_by_id($id);
  return drupal_get_form('pets_owners_storage_edit_form', $owner);
}

/**
 * Render a list of entries in the database.
 */
function pets_owners_storage_admin_page() {
  $output = '';

  if ($owners = all_pets_owners_in_db()) {
    $rows = array();
    foreach ($owners as $owner) {
      $rows[] = array(
        $owner->id,
        htmlentities($owner->first_name),
        htmlentities($owner->last_name),
        htmlentities($owner->email),
        l(t('Edit'), 'pets_owners_storage/pets_owners_form/' . $owner->id, array('attributes' => array('class' => 'edit-link'))),
        l(t('Delete'), 'pets_owners_storage/confirm_delete/' . $owner->id, array('attributes' => array('class' => 'delete-link')))
      );

    }
    $header = array(
      t('Id'),
      t('First Name'),
      t('Last Name'),
      t('E-mail'),
      t('Edit'),
      t('Delete')
    );
    $build['pager_table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('There are no date formats found in the db'),
    );


    // Attach the pager theme.
    $build['pager_pager'] = array('#theme' => 'pager');
    $build['pager_link'] = array(
      '#markup' => l(t('Add pets Owner'), 'pets_owners_storage/pets_owners_form', array('attributes' => array('class' => 'add-link'))),
    );

  }
  else {
    drupal_set_message(t('No entries have been added yet.'));
  }
  return $build;
}

