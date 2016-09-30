<?php

function pets_owners_storage_delete_callback($id = 'all') {
  delete_pet_owner_by_id($id);
  drupal_goto('pets_owners_storage/pets_owners_page');
}