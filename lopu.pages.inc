<?php
/**
 * A moal statis page callback
 * @param $js boolean determines if js is enable at user's browser end or not.
 * @return string the HTML, parsed by Drupapl to show the login form.
 **/
function ctools_modal_page($js = NULL) {
	if ($js) {
		// Required includes for ctools to work
		ctools_include('ajax');
		ctools_include('modal');
		$form_state = array(
			'ajax' => TRUE,
			'title' => t('User Login'),
		);
		$output = ctools_modal_form_wrapper('user_login', $form_state);
		if (!empty($form_state['executed'])) {
			// We'll just overwrite the form output if it was successful.
			$output = array();
			ctools_add_js('ajax-responder');
			$output[] = ctools_modal_command_dismiss(t('Login success'));
			if (isset($_GET['destination'])) {
				$output[] = ctools_ajax_command_redirect($_GET['destination']);
			} else {
				$output[] = ctools_ajax_command_reload();
			}
		}
		print ajax_render($output);
	} else {
		return drupal_get_form('user_login');
	}
}

/**
 * Closes modal windows.
 */
function lopu_dismiss($js = NULL) {
    if (!$js) {
      // we should never be here out of ajax context
      return MENU_NOT_FOUND;
    }
  
    ctools_include('modal');
    ctools_include('ajax');
  
    $output = array(ctools_modal_command_dismiss());
  
    print ajax_render($output);
}

/**
 * Page callback to display login link (OPTIONAL)
 **/
function ctools_ajax_sample_page() {
	// Required includes for ctools to work
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
	$str = "";
	if (user_is_anonymous()) {
		$str = "Hi, This is my brand new page, created just to show ";
		$str .= l("Ctools Login link", "lopu/nojs/login", array(
							'attributes' => array(
								'class' => array(
									'ctools-use-modal',
									'ctools-modal-custom',
								)
							)
						));
	}
	return $str;
}
