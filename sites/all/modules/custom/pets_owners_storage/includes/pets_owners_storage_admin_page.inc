<?php
/**
 * Render a list of entries in the database.
 */
function pets_owners_storage_admin_page() {
  $output = '';

  if ($owners = all_pets_owners_in_db()) {
    $rows = array();
    foreach ($owners as $owner) {
      $rows[] = array(
        $owner -> id,
        $owner -> first_name,
        $owner -> last_name,
        $owner -> email,
        l(t('Edit'), 'pets_owners_storage/edit_form/' . $owner->id, array('attributes' => array('class' => 'edit-link'))),
        l(t('Delete'), 'pets_owners_storage/delete_owner/' . $owner->id, array('attributes' => array('class' => 'delete-link')))
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
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    $output .= l(t('Add pets Owner'), 'pets_owners_storage/add_form', array('attributes' => array('class' => 'add-link')));
  }
  else {
    drupal_set_message(t('No entries have been added yet.'));
  }
  return $output;
}

