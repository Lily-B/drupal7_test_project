<?php
/**
 * Custom validation rules for this module for fapi_validation.
 * @return array with all the included in function rules for this module.
 */
function d7_fapi_validation_rules() {
  return array(
    'alpha_space' => array(
      'callback' => 'd7_validation_alpha_space',
      'error_msg' => 'Invalid value for %field. You can only Use letters and space.'
    )
  );
}

/**
 * alpha_space validation rule for fapi_validation
 * @param $value
 * @return bool
 */
function d7_validation_alpha_space($value) {
  if (preg_match('/^[a-zA-Z ]*$/', $value)) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}