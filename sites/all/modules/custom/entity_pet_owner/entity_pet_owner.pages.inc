<?php


/**
 * Callback for entity type page
 */
function entity_pet_owner_entity_page() {

  $pet_owners = entity_load('pet_owner', array(1,2,3) );
  $output = array();
//  foreach ($pet_owners as $owner) {
//    $output[] .= '<em>' . $owner->first_name . '</em>';
//    $output[] .= '<br>';
//    $output[] .= $owner->last_name;
//    $output[] .= '<br>';
//    $output[] .= $owner->city;
//    $output[] .= '<br>';
//    $output[] .= 'Birthday: ' . date('d F, Y', check_plain($owner->birthday_timestamp));
//    $output[] .= '<br>';
//    $output[] .= '<br>';
////  }

  $list = entity_view('pet_owner', $pet_owners);


  foreach ($list['pet_owner'] as $owner) {
    $output[] = drupal_render($owner);
  }

  dpm($pet_owners);
  return implode($output);
}

/**
 * Callback function for displaying the individual project page
 * @param $id
 * @return bool
 */
function entity_pet_owner_callback($id) {

  $owners = entity_load('pet_owner', array($id));
  $owner = $owners[$id];

  drupal_set_title($owner->first_name . ' ' . $owner->last_name);
  $output = entity_view('pet_owner', array($owner));
  return $output;
}
