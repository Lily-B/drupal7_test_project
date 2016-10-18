<?php


/**
 * Callback for entity type page
 */
function entity_pet_owner_entity_page(){

  $pet_owners = entity_load('pet_owner', array(9, 24));
  $list = entity_view('pet_owner', $pet_owners);

  $output = array();
  foreach ($list['pet_owner'] as $owner) {
    $output[] = drupal_render($owner);
  }

  dpm($pet_owners);
  return implode($output);
}
