$(document).ready(function() {

    function randomNumber(min, max) {
        return Math.floor(Math.random() * (max - min + 1) + min);
    }
    $('#captchaOperation').html([randomNumber(1, 100), '+', randomNumber(1, 200), '='].join(' '));

    $('#datePicker')
    .datepicker({
        format: 'mm/dd/yyyy'
    })
    .on('changeDate', function(e) {
        // Revalidate the date field
        $('#regForm').formValidation('revalidateField', 'i_tanggal_lahir');
    });

    $('#regForm')
    .find('[name="i_agama"]')
        .selectpicker()
        .change(function(e) {
            // revalidate the language when it is changed
            $('#regForm').formValidation('revalidateField', 'i_agama');
        })
        .end()
    .find('[name="i_pekerjaan"]')
        .selectpicker()
        .change(function(e) {
            // revalidate the language when it is changed
            $('#regForm').formValidation('revalidateField', 'i_pekerjaan');
        })
        .end()
    .find('[name="i_prodi"]')
        .selectpicker()
        .change(function(e) {
            // revalidate the language when it is changed
            $('#regForm').formValidation('revalidateField', 'i_prodi');
        })
        .end()
    .formValidation({
        framework: 'bootstrap',
        excluded: ':disabled',
        icon: {
            valid: 'glyphicon glyphicon-ok',
            invalid: 'glyphicon glyphicon-remove',
            validating: 'glyphicon glyphicon-refresh'
        },
        fields: {
            i_nama: {
                validators: {
                    notEmpty: {
                        message: 'The name is required'
                    },
                    regexp: {
                        message: 'The name can only contain the text, and spaces.',
                        regexp: /^[a-zA-Z]+$/
                    }
                }
            },
            i_tempat_lahir: {
                validators: {
                    notEmpty: {
                        message: 'The name is required'
                    }
                }
            },
            i_tanggal_lahir: {
                validators: {
                    notEmpty: {
                        message: 'The date is required'
                    },
                    date: {
                        format: 'MM/DD/YYYY',
                        message: 'The date is not a valid'
                    }
                }
            },
            i_jenis_kelamin: {
                validators: {
                    notEmpty: {
                        message: 'Please select your native jenis kelamin.'
                    }
                }
            },
            i_agama: {
                validators: {
                    notEmpty: {
                        message: 'Please select your native agama.'
                    }
                }
            },
            i_nomor_telepon: {
                validators: {
                    notEmpty: {
                        message: 'The phone number is required'
                    },
                    regexp: {
                        message: 'The phone number can only contain the digits, spaces, -, (, ), + and .',
                        regexp: /^[0-9\s\-()+\.]+$/
                    }
                }
            },
            i_alamat: {
                validators: {
                    notEmpty: {
                        message: 'Alamat diperlukan.'
                    },
                }
            },
            i_pekerjaan: {
                validators: {
                    notEmpty: {
                        message: 'The gender is required'
                    }
                }
            },
            i_detail_pekerjaan: {
                validators: {
                    notEmpty: {
                        message: 'The gender is required'
                    }
                }
            },
            i_prodi: {
                validators: {
                    notEmpty: {
                        message: 'The gender is required'
                    }
                }
            },
            i_tahun_masuk: {
                row: '.col-sm-4',
                validators: {
                    notEmpty: {
                        message: 'Tahun masuk diperlukan.'
                    },
                    regexp: {
                        regexp: /^[0-9_\.]+$/,
                        message: 'Tahun masuk hanya bisa di isi tahun ex 2016. '
                    },
                }
            },
            i_tahun_lulus: {
                row: '.col-sm-4',
                validators: {
                    notEmpty: {
                        message: 'Tahun lulus diperlukan.'
                    },
                    regexp: {
                        regexp: /^[0-9_\.]+$/,
                        message: 'Tahun lulus hanya bisa di isi tahun ex 2016.'
                    },
                }
            },
            i_email: {
                verbose: false,
                validators: {
                    notEmpty: {
                        message: 'The email address is required and can\'t be empty'
                    },
                    emailAddress: {
                        message: 'The input is not a valid email address'
                    },
                    stringLength: {
                        max: 512,
                        message: 'Cannot exceed 512 characters'
                    }
                }
            },
            password: {
                validators: {
                    notEmpty: {
                        message: 'Password diperlukan.'
                    },
                    stringLength: {
                        min: 6,
                        max: 30,
                        message: 'Password harus lebih dari 6 dan kurang dari 30 karakter.'
                    },
                    regexp: {
                        regexp: /^[a-zA-Z0-9_\.]+$/,
                        message: 'Password hanya bisa terdiri dari abjad, angka , titik dan garis bawah.'
                    }
                }
            },
            confirmPassword: {
                validators: {
                    notEmpty: {
                        message: 'Password diperlukan.'
                    },
                    identical: {
                        field: 'password',
                        message: 'Password Anda tidak sesuai.'
                    }
                }
            },
            captcha: {
                validators: {
                    callback: {
                        message: 'Wrong answer',
                        callback: function(value, validator, $field) {
                            var items = $('#captchaOperation').html().split(' '), sum = parseInt(items[0]) + parseInt(items[2]);
                            return value == sum;
                        }
                    }
                }
            }
        }
    });
});

$('.selectpicker').selectpicker({
  style: 'btn-info',
  size: 4
});

/*


$(document).on('change', '.btn-file :file', function() {
  var input = $(this),
      numFiles = input.get(0).files ? input.get(0).files.length : 1,
      label = input.val().replace(/\\/g, '/').replace(/.*\//, '');
  input.trigger('fileselect', [numFiles, label]);
});

$(document).ready( function() {
    $('.btn-file :file').on('fileselect', function(event, numFiles, label) {
        
        var input = $(this).parents('.input-group').find(':text'),
            log = numFiles > 1 ? numFiles + ' files selected' : label;
        
        if( input.length ) {
            input.val(log);
        } else {
            if( log ) alert(log);
        }
        
    });
});

*/
