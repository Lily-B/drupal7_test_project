<?php

/**
 * Confirm page for delete with 2 links
 * @param string $id
 * @return string
 */
function pets_owners_storage_confirm_callback($id) {
  $owner = find_pet_owner_by_id($id);
  $output = '<h2>Are you sure, you want to delete '
    . check_plain($owner->first_name) . ' '
    . check_plain($owner->last_name) . '?</h2>';
  $output .= l(t('Delete'), 'pets_owners_storage/delete_owner/'
    . $owner->id, array('attributes' => array('class' => 'delete-link')));
  $output .= '&nbsp;&nbsp;&nbsp;';
  $output .= l(t('Cancel'), 'pets_owners_storage/pets_owners_page',
    array('attributes' => array('class' => 'cancel-link')));
  return $output;
}

/**
 * @param $id
 */
function pets_owners_storage_delete_callback($id) {
  if (user_access('access all pets owners table')) {
    delete_pet_owner_by_id($id);
    cache_clear_all('pets_owners_storage_owners_table_rows_', 'cache_pets_owners_storage', TRUE);
    cache_clear_all('pets_owners', 'cache_views_data', TRUE);
  }
  else {
    drupal_access_denied();
  };

  drupal_goto('pets_owners_storage/pets_owners_page');
}

/**
 * Render a list of entries in the database.
 */
function pets_owners_storage_admin_page() {

  $build = '';
//  if ($cache = cache_get('pets_owners_storage_owners' . pager_find_page(), 'cache_pets_owners_storage')) {
//    $owners = $cache->data;
//  }
//  else{
//    $owners = all_pets_owners_in_db();
//    cache_set('pets_owners_storage_owners' . pager_find_page(), $owners, 'cache_pets_owners_storage');
//  }

  $owners = all_pets_owners_in_db();

  if ($owners) {
    $rows = [];
    if ($cache = cache_get('pets_owners_storage_owners_table_rows_' . pager_find_page(), 'cache_pets_owners_storage')) {
      $rows = $cache->data;
    }
    else {
      $pets = get_all_terms_of_vocab('pets');

      foreach ($owners as $owner) {
        $rows[] = [
          $owner->id,
          check_plain($owner->first_name),
          check_plain($owner->last_name),
          format_date($owner->birthday_timestamp, 'custom', 'Y-m-d'),
          check_plain($owner->email),
          check_plain($owner->city),
          $pets[$owner->pet],
          l(t('Edit'), 'pets_owners_storage/pets_owners_form/' . $owner->id, array('attributes' => array('class' => 'edit-link'))),
          l(t('Delete'), 'pets_owners_storage/confirm_delete/' . $owner->id, array('attributes' => array('class' => 'delete-link')))
        ];
      }
      drupal_get_query_parameters();
      cache_set('pets_owners_storage_owners_table_rows_' . pager_find_page(), $rows, 'cache_pets_owners_storage');
    }
    $header = array(
      t('Id'),
      t('First Name'),
      t('Last Name'),
      t('Owners Birthday'),
      t('E-mail'),
      t('City'),
      t('Pet'),
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

/**
 * Color menu item callback;
 * @return string
 */
function pets_owners_storage_colored_menu_callback() {
  drupal_add_js('misc/ajax.js');
  drupal_add_js(drupal_get_path('module', 'pets_owners_storage') . '/includes/js/colored_menu.js');
  return 'My colored Menu';
}

/**
 * function for ajax colored menu
 * @return array
 */
function pets_owners_storage_colors_callback() {
  $red = rand(0, 200);
  $green = rand(0, 200);
  $blue = rand(0, 200);
  $color_rgba = 'rgba(' . $red . ',' . $green . ',' . $blue . ',0.3';

  $response =array(
    '#type' => 'ajax',
    '#commands' => array(
      array(
        'command' => 'new_color',
        'color' => $color_rgba,
      ),
    ),
  );

  return $response;
}

/**
 * Callback for entity type page
 */
//function pets_owners_storage_entity_page(){
//
//  $pet_owners = entity_load('pet_owner', array(9, 24));
//  $list = entity_view('pet_owner', $pet_owners);
//
//  $output = array();
//  foreach ($list['pet_owner'] as $owner) {
//    $output[] = drupal_render($owner);
//  }
//
//  dpm($pet_owners);
//  return implode($output);
//}
