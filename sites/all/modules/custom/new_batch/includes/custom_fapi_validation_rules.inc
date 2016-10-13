<?php
/**
 * Custom validation rules for this module for fapi_validation.
 * @return array with all the included in function rules for this module.
 */
function new_batch_fapi_validation_rules() {
  return array(
    'alpha_dash' => array(
      'callback' => 'new_batch_validation_alpha_dash',
      'error_msg' => 'Invalid value for %field. You can only Use letters and dash.'
    )
  );
}

/**
 * alpha_space validation rule for fapi_validation
 * @param $value
 * @return bool
 */
function new_batch_validation_alpha_dash($value) {
  if (preg_match('/^[a-zA-Z-]*$/', $value)) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}