$('form').submit ->
  $.post $(this).attr('action'), $(this).serialize(), form_did_load
  false

