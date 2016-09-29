<?php
/**
 * Render a list of entries in the database.
 */
function pets_owners_storage_admin_page() {
  $output = '';

// Get all entries in pets_owners_storage table.
  if ($owners = all_pets_owners_in_db()) {
    $rows = array();
    foreach ($owners as $owner) {
//      echo(var_dump($owner->id));
// Sanitize the data before handing it off to the theme layer.
      $rows[] = array(
        $owner -> id,
        $owner -> first_name,
        $owner -> last_name,
        $owner -> email,
        l(t('Edit'), 'pets_owners_storage/edit?id=' . $owner->id, array('attributes' => array('class' => 'edit-link'))),
        l(t('Delete'), 'pets_owners_storage/delete?id=' . $owner->id, array('attributes' => array('class' => 'delete-link')))
      );

    }

// Make a table for them.
    $header = array(
      t('Id'),
      t('First Name'),
      t('Last Name'),
      t('E-mail'),
      t('Edit'),
      t('Delete')
    );
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }
  else {
    drupal_set_message(t('No entries have been added yet.'));
  }
  return $output;
}

