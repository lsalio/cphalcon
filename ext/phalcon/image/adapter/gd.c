
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/file.h"
#include "ext/spl/spl_exceptions.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
ZEPHIR_INIT_CLASS(Phalcon_Image_Adapter_Gd) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Image\\Adapter, Gd, phalcon, image_adapter_gd, phalcon_image_adapter_ce, phalcon_image_adapter_gd_method_entry, 0);

	zend_class_implements(phalcon_image_adapter_gd_ce TSRMLS_CC, 1, phalcon_image_adapterinterface_ce);
	return SUCCESS;

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, check) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_8 = NULL;
	zval *version = NULL, *info = NULL, *matches, *_0, _1 = zval_used_for_init, *_2 = NULL, *_4, *_5, _6, _7, *_9, *_10, *_11;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_static_property_ce(phalcon_image_adapter_gd_ce, SL("_checked") TSRMLS_CC);
	if (zephir_is_true(_0)) {
		RETURN_MM_BOOL(1);
	}
	if (!((zephir_function_exists_ex(SS("gd_info") TSRMLS_CC) == SUCCESS))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_image_exception_ce, "GD is either not installed or not enabled, check your configuration");
		return;
	}
	ZEPHIR_INIT_VAR(version);
	ZVAL_NULL(version);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "GD_VERSION", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "defined", &_3, &_1);
	zephir_check_call_status();
	if (zephir_is_true(_2)) {
		ZEPHIR_INIT_BNVAR(version);
		ZEPHIR_GET_CONSTANT(version, "GD_VERSION");
	} else {
		ZEPHIR_CALL_FUNCTION(&info, "gd_info", NULL);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(matches);
		ZVAL_NULL(matches);
		ZEPHIR_INIT_VAR(_4);
		zephir_array_fetch_string(&_5, info, SL("GD Version"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_STRING(&_1, "/\\d+\\.\\d+(?:\\.\\d+)?/", 0);
		zephir_preg_match(_4, &(_4), &_1, _5, matches, 0, 0 , 0  TSRMLS_CC);
		if (zephir_is_true(_4)) {
			ZEPHIR_OBS_NVAR(version);
			zephir_array_fetch_long(&version, matches, 0, PH_NOISY TSRMLS_CC);
		}
	}
	ZEPHIR_SINIT_VAR(_6);
	ZVAL_STRING(&_6, "2.0.1", 0);
	ZEPHIR_SINIT_VAR(_7);
	ZVAL_STRING(&_7, ">=", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "version_compare", &_8, version, &_6, &_7);
	zephir_check_call_status();
	if (!(zephir_is_true(_2))) {
		ZEPHIR_INIT_VAR(_9);
		object_init_ex(_9, phalcon_image_exception_ce);
		ZEPHIR_INIT_VAR(_10);
		ZEPHIR_CONCAT_SV(_10, "Phalcon\\Image\\Adapter\\GD requires GD version '2.0.1' or greater, you have ", version);
		ZEPHIR_CALL_METHOD(NULL, _9, "__construct", NULL, _10);
		zephir_check_call_status();
		zephir_throw_exception(_9 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_static_property_ce(phalcon_image_adapter_gd_ce, SL("_checked"), ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
	_11 = zephir_fetch_static_property_ce(phalcon_image_adapter_gd_ce, SL("_checked") TSRMLS_CC);
	RETURN_CTOR(_11);

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, __construct) {

	zend_bool _15;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_5 = NULL;
	int width, height, ZEPHIR_LAST_CALL_STATUS;
	zval *file_param = NULL, *width_param = NULL, *height_param = NULL, *imageinfo = NULL, *_0, *_1, *_2 = NULL, *_4, *_6, *_7, *_8, *_9, *_10, *_11, *_12 = NULL, *_13 = NULL, *_14 = NULL, *_16, *_17, *_18;
	zval *file = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &file_param, &width_param, &height_param);

	if (Z_TYPE_P(file_param) != IS_STRING && Z_TYPE_P(file_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'file' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(file_param) == IS_STRING) {
		file = file_param;
	} else {
		ZEPHIR_INIT_VAR(file);
		ZVAL_EMPTY_STRING(file);
	}
	if (!width_param) {
		width = 0;
	} else {
		width = zephir_get_intval(width_param);
	}
	if (!height_param) {
		height = 0;
	} else {
		height = zephir_get_intval(height_param);
	}


	_0 = zephir_fetch_static_property_ce(phalcon_image_adapter_gd_ce, SL("_checked") TSRMLS_CC);
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_SELF(NULL, "check", NULL);
		zephir_check_call_status();
	}
	zephir_update_property_this(this_ptr, SL("_file"), file TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
	if ((zephir_file_exists(_0 TSRMLS_CC) == SUCCESS)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_2, "realpath", &_3, _1);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_realpath"), _2 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&imageinfo, "getimagesize", &_5, _4);
		zephir_check_call_status();
		if (zephir_is_true(imageinfo)) {
			zephir_array_fetch_long(&_6, imageinfo, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("_width"), _6 TSRMLS_CC);
			zephir_array_fetch_long(&_7, imageinfo, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("_height"), _7 TSRMLS_CC);
			zephir_array_fetch_long(&_8, imageinfo, 2, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("_type"), _8 TSRMLS_CC);
			zephir_array_fetch_string(&_9, imageinfo, SL("mime"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("_mime"), _9 TSRMLS_CC);
		}
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_type"), PH_NOISY_CC);
		do {
			if (ZEPHIR_IS_LONG(_10, 1)) {
				_11 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
				ZEPHIR_CALL_FUNCTION(&_12, "imagecreatefromgif", NULL, _11);
				zephir_check_call_status();
				zephir_update_property_this(this_ptr, SL("_image"), _12 TSRMLS_CC);
				break;
			}
			if (ZEPHIR_IS_LONG(_10, 2)) {
				_11 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
				ZEPHIR_CALL_FUNCTION(&_12, "imagecreatefromjpeg", NULL, _11);
				zephir_check_call_status();
				zephir_update_property_this(this_ptr, SL("_image"), _12 TSRMLS_CC);
				break;
			}
			if (ZEPHIR_IS_LONG(_10, 3)) {
				_11 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
				ZEPHIR_CALL_FUNCTION(&_12, "imagecreatefrompng", NULL, _11);
				zephir_check_call_status();
				zephir_update_property_this(this_ptr, SL("_image"), _12 TSRMLS_CC);
				break;
			}
			if (ZEPHIR_IS_LONG(_10, 15)) {
				_11 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
				ZEPHIR_CALL_FUNCTION(&_12, "imagecreatefromwbmp", NULL, _11);
				zephir_check_call_status();
				zephir_update_property_this(this_ptr, SL("_image"), _12 TSRMLS_CC);
				break;
			}
			if (ZEPHIR_IS_LONG(_10, 16)) {
				_11 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
				ZEPHIR_CALL_FUNCTION(&_12, "imagecreatefromxbm", NULL, _11);
				zephir_check_call_status();
				zephir_update_property_this(this_ptr, SL("_image"), _12 TSRMLS_CC);
				break;
			}
			_11 = zephir_fetch_nproperty_this(this_ptr, SL("_mime"), PH_NOISY_CC);
			if (zephir_is_true(_11)) {
				ZEPHIR_INIT_VAR(_13);
				object_init_ex(_13, phalcon_image_exception_ce);
				_11 = zephir_fetch_nproperty_this(this_ptr, SL("_mime"), PH_NOISY_CC);
				ZEPHIR_INIT_VAR(_14);
				ZEPHIR_CONCAT_SVS(_14, "Installed GD does not support ", _11, " images");
				ZEPHIR_CALL_METHOD(NULL, _13, "__construct", NULL, _14);
				zephir_check_call_status();
				zephir_throw_exception(_13 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_THROW_EXCEPTION_STR(phalcon_image_exception_ce, "Installed GD does not support such images");
				return;
			}
			break;
		} while(0);

		_11 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagesavealpha", NULL, _11, ZEPHIR_GLOBAL(global_true));
		zephir_check_call_status();
	} else {
		_15 = !width;
		if (!(_15)) {
			_15 = !height;
		}
		if (_15) {
			ZEPHIR_INIT_LNVAR(_13);
			object_init_ex(_13, phalcon_image_exception_ce);
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
			ZEPHIR_INIT_LNVAR(_14);
			ZEPHIR_CONCAT_SV(_14, "Failed to create image from file ", _1);
			ZEPHIR_CALL_METHOD(NULL, _13, "__construct", NULL, _14);
			zephir_check_call_status();
			zephir_throw_exception(_13 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(_16);
		ZVAL_LONG(_16, width);
		ZEPHIR_INIT_VAR(_17);
		ZVAL_LONG(_17, height);
		ZEPHIR_CALL_FUNCTION(&_2, "imagecreatetruecolor", NULL, _16, _17);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_image"), _2 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagealphablending", NULL, _4, ZEPHIR_GLOBAL(global_true));
		zephir_check_call_status();
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagesavealpha", NULL, _10, ZEPHIR_GLOBAL(global_true));
		zephir_check_call_status();
		_11 = zephir_fetch_nproperty_this(this_ptr, SL("_file"), PH_NOISY_CC);
		zephir_update_property_this(this_ptr, SL("_realpath"), _11 TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_18);
		ZVAL_LONG(_18, width);
		zephir_update_property_zval(this_ptr, SL("_width"), _18 TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_18);
		ZVAL_LONG(_18, height);
		zephir_update_property_zval(this_ptr, SL("_height"), _18 TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_18);
		ZVAL_LONG(_18, 3);
		zephir_update_property_this(this_ptr, SL("_type"), _18 TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_18);
		ZVAL_STRING(_18, "image/png", 1);
		zephir_update_property_this(this_ptr, SL("_mime"), _18 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _resize) {

	zend_bool _5, _8;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_7 = NULL;
	zval *width_param = NULL, *height_param = NULL, *image = NULL, *pre_width = NULL, *pre_height = NULL, *reduction_width = NULL, *reduction_height = NULL, *_0, _1 = zval_used_for_init, *_2 = NULL, *_4, *_6, *_9, *_10, *_11, *_12 = NULL, *_13 = NULL, *_14 = NULL, *_15 = NULL, *_16 = NULL, *_17, *_18, *_19, *_20 = NULL;
	int width, height, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &width_param, &height_param);

	width = zephir_get_intval(width_param);
	height = zephir_get_intval(height_param);


	ZEPHIR_INIT_VAR(image);
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_GET_CONSTANT(_0, "PHP_VERSION");
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "5.5.0", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "version_compare", &_3, _0, &_1);
	zephir_check_call_status();
	if (ZEPHIR_LT_LONG(_2, 0)) {
		ZEPHIR_OBS_VAR(pre_width);
		zephir_read_property_this(&pre_width, this_ptr, SL("_width"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(pre_height);
		zephir_read_property_this(&pre_height, this_ptr, SL("_height"), PH_NOISY_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		_5 = width > ((zephir_get_numberval(_4) / 2));
		if (_5) {
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
			_5 = height > ((zephir_get_numberval(_6) / 2));
		}
		if (_5) {
			ZEPHIR_SINIT_NVAR(_1);
			ZVAL_LONG(&_1, (width * 1.1));
			ZEPHIR_CALL_FUNCTION(&reduction_width, "round", &_7, &_1);
			zephir_check_call_status();
			ZEPHIR_SINIT_NVAR(_1);
			ZVAL_LONG(&_1, (height * 1.1));
			ZEPHIR_CALL_FUNCTION(&reduction_height, "round", &_7, &_1);
			zephir_check_call_status();
			while (1) {
				_8 = ZEPHIR_LT_LONG(reduction_width, (zephir_get_numberval(pre_width) / 2));
				if (_8) {
					_8 = ZEPHIR_LT_LONG(reduction_height, (zephir_get_numberval(pre_height) / 2));
				}
				if (!(_8)) {
					break;
				}
				ZEPHIR_INIT_NVAR(pre_width);
				ZVAL_DOUBLE(pre_width, 2);
				ZEPHIR_INIT_NVAR(pre_height);
				ZVAL_DOUBLE(pre_height, 2);
			}
			ZEPHIR_CALL_METHOD(&image, this_ptr, "_create", NULL, pre_width, pre_height);
			zephir_check_call_status();
			_9 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			_10 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
			_11 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
			ZEPHIR_INIT_VAR(_12);
			ZVAL_LONG(_12, 0);
			ZEPHIR_INIT_VAR(_13);
			ZVAL_LONG(_13, 0);
			ZEPHIR_INIT_VAR(_14);
			ZVAL_LONG(_14, 0);
			ZEPHIR_INIT_VAR(_15);
			ZVAL_LONG(_15, 0);
			ZEPHIR_CALL_FUNCTION(&_16, "imagecopyresized", NULL, image, _9, _12, _13, _14, _15, pre_width, pre_height, _10, _11);
			zephir_check_call_status();
			if (zephir_is_true(_16)) {
				_17 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
				ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _17);
				zephir_check_call_status();
				zephir_update_property_this(this_ptr, SL("_image"), image TSRMLS_CC);
			}
		}
		ZEPHIR_INIT_NVAR(_12);
		ZVAL_LONG(_12, width);
		ZEPHIR_INIT_NVAR(_13);
		ZVAL_LONG(_13, height);
		ZEPHIR_CALL_METHOD(&image, this_ptr, "_create", NULL, _12, _13);
		zephir_check_call_status();
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_12);
		ZVAL_LONG(_12, 0);
		ZEPHIR_INIT_NVAR(_13);
		ZVAL_LONG(_13, 0);
		ZEPHIR_INIT_NVAR(_14);
		ZVAL_LONG(_14, 0);
		ZEPHIR_INIT_NVAR(_15);
		ZVAL_LONG(_15, 0);
		ZEPHIR_INIT_VAR(_18);
		ZVAL_LONG(_18, width);
		ZEPHIR_INIT_VAR(_19);
		ZVAL_LONG(_19, height);
		ZEPHIR_CALL_FUNCTION(&_16, "imagecopyresampled", NULL, image, _9, _12, _13, _14, _15, _18, _19, pre_width, pre_height);
		zephir_check_call_status();
		if (zephir_is_true(_16)) {
			_10 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _10);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("_image"), image TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_16, "imagesx", NULL, image);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("_width"), _16 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_20, "imagesy", NULL, image);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("_height"), _20 TSRMLS_CC);
		}
	} else {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_12);
		ZVAL_LONG(_12, width);
		ZEPHIR_INIT_NVAR(_13);
		ZVAL_LONG(_13, height);
		ZEPHIR_CALL_FUNCTION(&image, "imagescale", NULL, _4, _12, _13);
		zephir_check_call_status();
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _6);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_image"), image TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_16, "imagesx", NULL, image);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_width"), _16 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_20, "imagesx", NULL, image);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_height"), _20 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _crop) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	zval *width_param = NULL, *height_param = NULL, *offset_x_param = NULL, *offset_y_param = NULL, *image = NULL, *rect, *_0, _1, *_2 = NULL, *_4 = NULL, *_5 = NULL, *_6, *_7, *_8, *_9, *_10, *_11, *_12, *_13 = NULL, *_14, *_15 = NULL;
	int width, height, offset_x, offset_y, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &width_param, &height_param, &offset_x_param, &offset_y_param);

	width = zephir_get_intval(width_param);
	height = zephir_get_intval(height_param);
	offset_x = zephir_get_intval(offset_x_param);
	offset_y = zephir_get_intval(offset_y_param);


	ZEPHIR_INIT_VAR(image);
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_GET_CONSTANT(_0, "PHP_VERSION");
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "5.5.0", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "version_compare", &_3, _0, &_1);
	zephir_check_call_status();
	if (ZEPHIR_LT_LONG(_2, 0)) {
		ZEPHIR_INIT_VAR(_4);
		ZVAL_LONG(_4, width);
		ZEPHIR_INIT_VAR(_5);
		ZVAL_LONG(_5, height);
		ZEPHIR_CALL_METHOD(&image, this_ptr, "_create", NULL, _4, _5);
		zephir_check_call_status();
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, 0);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_LONG(_5, 0);
		ZEPHIR_INIT_VAR(_7);
		ZVAL_LONG(_7, offset_x);
		ZEPHIR_INIT_VAR(_8);
		ZVAL_LONG(_8, offset_y);
		ZEPHIR_INIT_VAR(_9);
		ZVAL_LONG(_9, width);
		ZEPHIR_INIT_VAR(_10);
		ZVAL_LONG(_10, height);
		ZEPHIR_INIT_VAR(_11);
		ZVAL_LONG(_11, width);
		ZEPHIR_INIT_VAR(_12);
		ZVAL_LONG(_12, height);
		ZEPHIR_CALL_FUNCTION(&_13, "imagecopyresampled", NULL, image, _6, _4, _5, _7, _8, _9, _10, _11, _12);
		zephir_check_call_status();
		if (zephir_is_true(_13)) {
			_14 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _14);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("_image"), image TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_13, "imagesx", NULL, image);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("_width"), _13 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_15, "imagesy", NULL, image);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("_height"), _15 TSRMLS_CC);
		}
	} else {
		ZEPHIR_INIT_VAR(rect);
		array_init_size(rect, 6);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, offset_x);
		zephir_array_update_string(&rect, SL("x"), &_4, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, offset_y);
		zephir_array_update_string(&rect, SL("y"), &_4, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, width);
		zephir_array_update_string(&rect, SL("width"), &_4, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, height);
		zephir_array_update_string(&rect, SL("height"), &_4, PH_COPY | PH_SEPARATE);
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&image, "imagecrop", NULL, _6, rect);
		zephir_check_call_status();
		_14 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _14);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_image"), image TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_13, "imagesx", NULL, image);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_width"), _13 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_15, "imagesx", NULL, image);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_height"), _15 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _rotate) {

	zval *degrees_param = NULL, *image = NULL, *transparent = NULL, *width = NULL, *height = NULL, *_0, _1, _2, _3, _4, *_5, *_6, *_7, *_8, *_9, *_10, *_11, *_12 = NULL, *_13;
	int degrees, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &degrees_param);

	degrees = zephir_get_intval(degrees_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, 0);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, 0);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_LONG(&_4, 127);
	ZEPHIR_CALL_FUNCTION(&transparent, "imagecolorallocatealpha", NULL, _0, &_1, &_2, &_3, &_4);
	zephir_check_call_status();
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_LONG(_6, (360 - degrees));
	ZEPHIR_INIT_VAR(_7);
	ZVAL_LONG(_7, 1);
	ZEPHIR_CALL_FUNCTION(&image, "imagerotate", NULL, _5, _6, transparent, _7);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "imagesavealpha", NULL, image, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&width, "imagesx", NULL, image);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&height, "imagesy", NULL, image);
	zephir_check_call_status();
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, 0);
	ZEPHIR_INIT_BNVAR(_7);
	ZVAL_LONG(_7, 0);
	ZEPHIR_INIT_VAR(_9);
	ZVAL_LONG(_9, 0);
	ZEPHIR_INIT_VAR(_10);
	ZVAL_LONG(_10, 0);
	ZEPHIR_INIT_VAR(_11);
	ZVAL_LONG(_11, 100);
	ZEPHIR_CALL_FUNCTION(&_12, "imagecopymerge", NULL, _8, image, _6, _7, _9, _10, width, height, _11);
	zephir_check_call_status();
	if (zephir_is_true(_12)) {
		_13 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _13);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_image"), image TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_width"), width TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_height"), height TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _flip) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	zval *direction_param = NULL, *image = NULL, *_0, _1, *_2 = NULL, *_4, *_5, *_6, *_7, *_8, *_9, *_10 = NULL, *_11 = NULL, *_12 = NULL, *_13 = NULL, *_14 = NULL, *_15 = NULL, *_16 = NULL;
	int direction, x, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &direction_param);

	direction = zephir_get_intval(direction_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_GET_CONSTANT(_0, "PHP_VERSION");
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "5.5.0", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "version_compare", &_3, _0, &_1);
	zephir_check_call_status();
	if (ZEPHIR_LT_LONG(_2, 0)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		_5 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&image, this_ptr, "_create", NULL, _4, _5);
		zephir_check_call_status();
		if (direction == 11) {
			x = 0;
			while (1) {
				_6 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
				if (!(ZEPHIR_GT_LONG(_6, x))) {
					break;
				}
				x++;
				_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
				_8 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
				_9 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_10);
				ZVAL_LONG(_10, x);
				ZEPHIR_INIT_NVAR(_11);
				ZVAL_LONG(_11, 0);
				ZEPHIR_INIT_NVAR(_12);
				ZVAL_LONG(_12, ((zephir_get_numberval(_8) - x) - 1));
				ZEPHIR_INIT_NVAR(_13);
				ZVAL_LONG(_13, 0);
				ZEPHIR_INIT_NVAR(_14);
				ZVAL_LONG(_14, 1);
				ZEPHIR_CALL_FUNCTION(NULL, "imagecopy", NULL, image, _7, _10, _11, _12, _13, _14, _9);
				zephir_check_call_status();
			}
		} else {
			x = 0;
			while (1) {
				_6 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
				if (!(ZEPHIR_GT_LONG(_6, x))) {
					break;
				}
				x++;
				_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
				_8 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
				_9 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_10);
				ZVAL_LONG(_10, 0);
				ZEPHIR_INIT_NVAR(_11);
				ZVAL_LONG(_11, x);
				ZEPHIR_INIT_NVAR(_12);
				ZVAL_LONG(_12, 0);
				ZEPHIR_INIT_NVAR(_13);
				ZVAL_LONG(_13, ((zephir_get_numberval(_8) - x) - 1));
				ZEPHIR_INIT_NVAR(_14);
				ZVAL_LONG(_14, 1);
				ZEPHIR_CALL_FUNCTION(NULL, "imagecopy", NULL, image, _7, _10, _11, _12, _13, _9, _14);
				zephir_check_call_status();
			}
		}
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _6);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_image"), image TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_15, "imagesx", NULL, image);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_width"), _15 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_16, "imagesy", NULL, image);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_height"), _16 TSRMLS_CC);
	} else {
		if (direction == 11) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_10);
			ZEPHIR_GET_CONSTANT(_10, "IMG_FLIP_HORIZONTAL");
			ZEPHIR_CALL_FUNCTION(NULL, "imageflip", NULL, _4, _10);
			zephir_check_call_status();
		} else {
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZEPHIR_GET_CONSTANT(_11, "IMG_FLIP_VERTICAL");
			ZEPHIR_CALL_FUNCTION(NULL, "imageflip", NULL, _5, _11);
			zephir_check_call_status();
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _sharpen) {

	zval *_5;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL;
	zval *amount_param = NULL, *matrix, _0 = zval_used_for_init, *_1 = NULL, *_3 = NULL, *_6, *_7, *_8, *_9 = NULL, *_10, *_11, *_12 = NULL;
	int amount, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &amount_param);

	amount = zephir_get_intval(amount_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, (-18 + ((amount * 0.08))));
	ZEPHIR_CALL_FUNCTION(&_1, "abs", &_2, &_0);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, 2);
	ZEPHIR_CALL_FUNCTION(&_3, "round", &_4, _1, &_0);
	zephir_check_call_status();
	amount = zephir_get_intval(_3);
	ZEPHIR_INIT_VAR(matrix);
	array_init_size(matrix, 4);
	ZEPHIR_INIT_VAR(_5);
	array_init_size(_5, 4);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	zephir_array_fast_append(matrix, _5);
	ZEPHIR_INIT_BNVAR(_5);
	array_init_size(_5, 4);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, amount);
	zephir_array_fast_append(_5, _6);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	zephir_array_fast_append(matrix, _5);
	ZEPHIR_INIT_BNVAR(_5);
	array_init_size(_5, 4);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, -1);
	zephir_array_fast_append(_5, _6);
	zephir_array_fast_append(matrix, _5);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, (amount - 8));
	ZEPHIR_INIT_VAR(_8);
	ZVAL_LONG(_8, 0);
	ZEPHIR_CALL_FUNCTION(&_9, "imageconvolution", NULL, _7, matrix, _6, _8);
	zephir_check_call_status();
	if (zephir_is_true(_9)) {
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_9, "imagesx", NULL, _10);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_width"), _9 TSRMLS_CC);
		_11 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_12, "imagesy", NULL, _11);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_height"), _12 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _reflection) {

	zephir_fcall_cache_entry *_18 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL;
	zend_bool fade_in;
	zval *height_param = NULL, *opacity_param = NULL, *fade_in_param = NULL, *reflection = NULL, *line = NULL, _0 = zval_used_for_init, *_1 = NULL, *_3 = NULL, *_5, *_6, *_7 = NULL, *_8, *_9, *_10, *_11 = NULL, *_12 = NULL, *_13 = NULL, *_14, *_15, *_16 = NULL, *_17, *_19, *_20, *_21 = NULL, *_22, *_23 = NULL, *_24 = NULL;
	int height, opacity, stepping, offset, src_y, dst_y, dst_opacity, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &height_param, &opacity_param, &fade_in_param);

	height = zephir_get_intval(height_param);
	opacity = zephir_get_intval(opacity_param);
	fade_in = zephir_get_boolval(fade_in_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, ((((opacity * 127) / 100)) - 127));
	ZEPHIR_CALL_FUNCTION(&_1, "abs", &_2, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_3, "round", &_4, _1);
	zephir_check_call_status();
	opacity = zephir_get_intval(_3);
	if (opacity < 127) {
		stepping = (((127 - opacity)) / height);
	} else {
		stepping = (127 / height);
	}
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_7);
	ZVAL_LONG(_7, (zephir_get_numberval(_6) + height));
	ZEPHIR_CALL_METHOD(&reflection, this_ptr, "_create", NULL, _5, _7);
	zephir_check_call_status();
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	_9 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
	_10 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
	ZEPHIR_INIT_BNVAR(_7);
	ZVAL_LONG(_7, 0);
	ZEPHIR_INIT_VAR(_11);
	ZVAL_LONG(_11, 0);
	ZEPHIR_INIT_VAR(_12);
	ZVAL_LONG(_12, 0);
	ZEPHIR_INIT_VAR(_13);
	ZVAL_LONG(_13, 0);
	ZEPHIR_CALL_FUNCTION(NULL, "imagecopy", NULL, reflection, _8, _7, _11, _12, _13, _9, _10);
	zephir_check_call_status();
	offset = 0;
	while (1) {
		if (!(height >= offset)) {
			break;
		}
		_14 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
		src_y = ((zephir_get_numberval(_14) - offset) - 1);
		_15 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
		dst_y = (zephir_get_numberval(_15) + offset);
		if (fade_in) {
			ZEPHIR_SINIT_NVAR(_0);
			ZVAL_LONG(&_0, (opacity + ((stepping * ((height - offset))))));
			ZEPHIR_CALL_FUNCTION(&_16, "round", &_4, &_0);
			zephir_check_call_status();
			dst_opacity = zephir_get_intval(_16);
		} else {
			ZEPHIR_SINIT_NVAR(_0);
			ZVAL_LONG(&_0, (opacity + ((stepping * offset))));
			ZEPHIR_CALL_FUNCTION(&_16, "round", &_4, &_0);
			zephir_check_call_status();
			dst_opacity = zephir_get_intval(_16);
		}
		_17 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_7);
		ZVAL_LONG(_7, 1);
		ZEPHIR_CALL_METHOD(&line, this_ptr, "_create", &_18, _17, _7);
		zephir_check_call_status();
		_19 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		_20 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_7);
		ZVAL_LONG(_7, 0);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_LONG(_11, 0);
		ZEPHIR_INIT_NVAR(_12);
		ZVAL_LONG(_12, 0);
		ZEPHIR_INIT_NVAR(_13);
		ZVAL_LONG(_13, src_y);
		ZEPHIR_INIT_NVAR(_21);
		ZVAL_LONG(_21, 1);
		ZEPHIR_CALL_FUNCTION(NULL, "imagecopy", NULL, line, _19, _7, _11, _12, _13, _20, _21);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_7);
		ZEPHIR_GET_CONSTANT(_7, "IMG_FILTER_COLORIZE");
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_LONG(_11, 0);
		ZEPHIR_INIT_NVAR(_12);
		ZVAL_LONG(_12, 0);
		ZEPHIR_INIT_NVAR(_13);
		ZVAL_LONG(_13, 0);
		ZEPHIR_INIT_NVAR(_21);
		ZVAL_LONG(_21, dst_opacity);
		ZEPHIR_CALL_FUNCTION(NULL, "imagefilter", NULL, line, _7, _11, _12, _13, _21);
		zephir_check_call_status();
		_22 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_LONG(_11, 0);
		ZEPHIR_INIT_NVAR(_12);
		ZVAL_LONG(_12, dst_y);
		ZEPHIR_INIT_NVAR(_13);
		ZVAL_LONG(_13, 0);
		ZEPHIR_INIT_NVAR(_21);
		ZVAL_LONG(_21, 0);
		ZEPHIR_INIT_NVAR(_23);
		ZVAL_LONG(_23, 1);
		ZEPHIR_CALL_FUNCTION(NULL, "imagecopy", NULL, reflection, line, _11, _12, _13, _21, _22, _23);
		zephir_check_call_status();
		offset++;
	}
	_14 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _14);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_image"), reflection TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&_16, "imagesx", NULL, reflection);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_width"), _16 TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&_24, "imagesy", NULL, reflection);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_height"), _24 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _watermark) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL, *_7 = NULL;
	int offset_x, offset_y, opacity, width, height, ZEPHIR_LAST_CALL_STATUS;
	zval *watermark, *offset_x_param = NULL, *offset_y_param = NULL, *opacity_param = NULL, *overlay = NULL, *color = NULL, *_0 = NULL, *_1 = NULL, *_2 = NULL, _3 = zval_used_for_init, *_4 = NULL, *_6 = NULL, _8, _9, _10, *_11 = NULL, *_12 = NULL, *_13 = NULL, *_14 = NULL, *_15 = NULL, *_16, *_17, *_18;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &watermark, &offset_x_param, &offset_y_param, &opacity_param);

	offset_x = zephir_get_intval(offset_x_param);
	offset_y = zephir_get_intval(offset_y_param);
	opacity = zephir_get_intval(opacity_param);


	if (!(zephir_instance_of_ev(watermark, phalcon_image_adapter_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'watermark' must be an instance of 'Phalcon\\Image\\Adapter'");
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, watermark, "render",  NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&overlay, "imagecreatefromstring", NULL, _0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "imagesavealpha", NULL, overlay, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_1, "imagesx", NULL, overlay);
	zephir_check_call_status();
	width = zephir_get_intval(_1);
	ZEPHIR_CALL_FUNCTION(&_2, "imagesy", NULL, overlay);
	zephir_check_call_status();
	height = zephir_get_intval(_2);
	if (opacity < 100) {
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, ((((opacity * 127) / 100)) - 127));
		ZEPHIR_CALL_FUNCTION(&_4, "abs", &_5, &_3);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_6, "round", &_7, _4);
		zephir_check_call_status();
		opacity = zephir_get_intval(_6);
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_LONG(&_3, 127);
		ZEPHIR_SINIT_VAR(_8);
		ZVAL_LONG(&_8, 127);
		ZEPHIR_SINIT_VAR(_9);
		ZVAL_LONG(&_9, 127);
		ZEPHIR_SINIT_VAR(_10);
		ZVAL_LONG(&_10, opacity);
		ZEPHIR_CALL_FUNCTION(&color, "imagecolorallocatealpha", NULL, overlay, &_3, &_8, &_9, &_10);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_11);
		ZEPHIR_GET_CONSTANT(_11, "IMG_EFFECT_OVERLAY");
		ZEPHIR_CALL_FUNCTION(NULL, "imagelayereffect", NULL, overlay, _11);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_12);
		ZVAL_LONG(_12, 0);
		ZEPHIR_INIT_VAR(_13);
		ZVAL_LONG(_13, 0);
		ZEPHIR_INIT_VAR(_14);
		ZVAL_LONG(_14, width);
		ZEPHIR_INIT_VAR(_15);
		ZVAL_LONG(_15, height);
		ZEPHIR_CALL_FUNCTION(NULL, "imagefilledrectangle", NULL, overlay, _12, _13, _14, _15, color);
		zephir_check_call_status();
	}
	_16 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_CALL_FUNCTION(NULL, "imagealphablending", NULL, _16, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	_17 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_11);
	ZVAL_LONG(_11, offset_x);
	ZEPHIR_INIT_NVAR(_12);
	ZVAL_LONG(_12, offset_y);
	ZEPHIR_INIT_NVAR(_13);
	ZVAL_LONG(_13, 0);
	ZEPHIR_INIT_NVAR(_14);
	ZVAL_LONG(_14, 0);
	ZEPHIR_INIT_NVAR(_15);
	ZVAL_LONG(_15, width);
	ZEPHIR_INIT_VAR(_18);
	ZVAL_LONG(_18, height);
	ZEPHIR_CALL_FUNCTION(&_4, "imagecopy", NULL, _17, overlay, _11, _12, _13, _14, _15, _18);
	zephir_check_call_status();
	if (zephir_is_true(_4)) {
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, overlay);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _text) {

	zephir_fcall_cache_entry *_20 = NULL;
	zend_bool _11, _12, _13;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL;
	int offset_x, offset_y, opacity, r, g, b, size, angle, s0 = 0, s1 = 0, s4 = 0, s5 = 0, width, height, ZEPHIR_LAST_CALL_STATUS;
	zval *text_param = NULL, *offset_x_param = NULL, *offset_y_param = NULL, *opacity_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *size_param = NULL, *fontfile_param = NULL, *space = NULL, *color = NULL, _0 = zval_used_for_init, *_1 = NULL, *_3 = NULL, *_5 = NULL, *_6 = NULL, *_7, *_8, *_9, *_10, *_14 = NULL, *_15 = NULL, *_16, _17 = zval_used_for_init, _18 = zval_used_for_init, _19 = zval_used_for_init, *_21, *_22 = NULL, *_23, *_24;
	zval *text = NULL, *fontfile = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 9, 0, &text_param, &offset_x_param, &offset_y_param, &opacity_param, &r_param, &g_param, &b_param, &size_param, &fontfile_param);

	zephir_get_strval(text, text_param);
	offset_x = zephir_get_intval(offset_x_param);
	offset_y = zephir_get_intval(offset_y_param);
	opacity = zephir_get_intval(opacity_param);
	r = zephir_get_intval(r_param);
	g = zephir_get_intval(g_param);
	b = zephir_get_intval(b_param);
	size = zephir_get_intval(size_param);
	zephir_get_strval(fontfile, fontfile_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, ((((opacity * 127) / 100)) - 127));
	ZEPHIR_CALL_FUNCTION(&_1, "abs", &_2, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_3, "round", &_4, _1);
	zephir_check_call_status();
	opacity = zephir_get_intval(_3);
	ZEPHIR_INIT_VAR(color);
	if (fontfile && Z_STRLEN_P(fontfile)) {
		ZEPHIR_INIT_VAR(_5);
		ZVAL_LONG(_5, size);
		ZEPHIR_INIT_VAR(_6);
		ZVAL_LONG(_6, 0);
		ZEPHIR_CALL_FUNCTION(&space, "imagettfbbox", NULL, _5, _6, fontfile, text);
		zephir_check_call_status();
		if (zephir_array_isset_long(space, 0)) {
			ZEPHIR_OBS_VAR(_7);
			zephir_array_fetch_long(&_7, space, 0, PH_NOISY TSRMLS_CC);
			s0 = zephir_get_intval(_7);
			ZEPHIR_OBS_VAR(_8);
			zephir_array_fetch_long(&_8, space, 1, PH_NOISY TSRMLS_CC);
			s1 = zephir_get_intval(_8);
			ZEPHIR_OBS_VAR(_9);
			zephir_array_fetch_long(&_9, space, 4, PH_NOISY TSRMLS_CC);
			s4 = zephir_get_intval(_9);
			ZEPHIR_OBS_VAR(_10);
			zephir_array_fetch_long(&_10, space, 5, PH_NOISY TSRMLS_CC);
			s5 = zephir_get_intval(_10);
		}
		_11 = !s0;
		if (!(_11)) {
			_11 = !s1;
		}
		_12 = _11;
		if (!(_12)) {
			_12 = !s4;
		}
		_13 = _12;
		if (!(_13)) {
			_13 = !s5;
		}
		if (_13) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_image_exception_ce, "Call to imagettfbbox() failed");
			return;
		}
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, (s4 - s0));
		ZEPHIR_CALL_FUNCTION(&_14, "abs", &_2, &_0);
		zephir_check_call_status();
		width = (zephir_get_numberval(_14) + 10);
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, (s5 - s1));
		ZEPHIR_CALL_FUNCTION(&_15, "abs", &_2, &_0);
		zephir_check_call_status();
		height = (zephir_get_numberval(_15) + 10);
		if (offset_x < 0) {
			_16 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
			offset_x = ((zephir_get_numberval(_16) - width) + offset_x);
		}
		if (offset_y < 0) {
			_16 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
			offset_y = ((zephir_get_numberval(_16) - height) + offset_y);
		}
		_16 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, r);
		ZEPHIR_SINIT_VAR(_17);
		ZVAL_LONG(&_17, g);
		ZEPHIR_SINIT_VAR(_18);
		ZVAL_LONG(&_18, b);
		ZEPHIR_SINIT_VAR(_19);
		ZVAL_LONG(&_19, opacity);
		ZEPHIR_CALL_FUNCTION(&color, "imagecolorallocatealpha", &_20, _16, &_0, &_17, &_18, &_19);
		zephir_check_call_status();
		angle = 0;
		_21 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_LONG(_5, size);
		ZEPHIR_INIT_NVAR(_6);
		ZVAL_LONG(_6, angle);
		ZEPHIR_INIT_VAR(_22);
		ZVAL_LONG(_22, offset_x);
		ZEPHIR_INIT_VAR(_23);
		ZVAL_LONG(_23, offset_y);
		ZEPHIR_CALL_FUNCTION(NULL, "imagettftext", NULL, _21, _5, _6, _22, _23, color, fontfile, text);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_LONG(_5, size);
		ZEPHIR_CALL_FUNCTION(&_14, "imagefontwidth", NULL, _5);
		zephir_check_call_status();
		width = (zephir_get_intval(_14) * zephir_fast_strlen_ev(text));
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_LONG(_5, size);
		ZEPHIR_CALL_FUNCTION(&_15, "imagefontheight", NULL, _5);
		zephir_check_call_status();
		height = zephir_get_intval(_15);
		if (offset_x < 0) {
			_21 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
			offset_x = ((zephir_get_numberval(_21) - width) + offset_x);
		}
		if (offset_y < 0) {
			_16 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
			offset_y = ((zephir_get_numberval(_16) - height) + offset_y);
		}
		_16 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, r);
		ZEPHIR_SINIT_NVAR(_17);
		ZVAL_LONG(&_17, g);
		ZEPHIR_SINIT_NVAR(_18);
		ZVAL_LONG(&_18, b);
		ZEPHIR_SINIT_NVAR(_19);
		ZVAL_LONG(&_19, opacity);
		ZEPHIR_CALL_FUNCTION(&color, "imagecolorallocatealpha", &_20, _16, &_0, &_17, &_18, &_19);
		zephir_check_call_status();
		_24 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_LONG(_5, size);
		ZEPHIR_INIT_NVAR(_6);
		ZVAL_LONG(_6, offset_x);
		ZEPHIR_INIT_NVAR(_22);
		ZVAL_LONG(_22, offset_y);
		ZEPHIR_CALL_FUNCTION(NULL, "imagestring", NULL, _24, _5, _6, _22, text, color);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _mask) {

	zend_bool _13;
	zephir_fcall_cache_entry *_9 = NULL, *_23 = NULL, *_24 = NULL;
	int mask_width, mask_height, x, y, ZEPHIR_LAST_CALL_STATUS, _26;
	zval *mask, *maskImage = NULL, *newimage = NULL, *tempImage = NULL, *color = NULL, *index = NULL, *alpha = NULL, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3, *_4, _5 = zval_used_for_init, _6 = zval_used_for_init, _7, _8, *_10 = NULL, *_11 = NULL, *_12, *_14, *_15, *_16, *_17, *_18, *_19, *_20, *_21, *_22, *_25, *_27, *_28;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &mask);



	if (!(zephir_instance_of_ev(mask, phalcon_image_adapter_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'mask' must be an instance of 'Phalcon\\Image\\Adapter'");
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, mask, "render",  NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&maskImage, "imagecreatefromstring", NULL, _0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_1, "imagesx", NULL, mask);
	zephir_check_call_status();
	mask_width = zephir_get_intval(_1);
	ZEPHIR_CALL_FUNCTION(&_2, "imagesy", NULL, mask);
	zephir_check_call_status();
	mask_height = zephir_get_intval(_2);
	ZEPHIR_INIT_VAR(alpha);
	ZVAL_LONG(alpha, 127);
	ZEPHIR_CALL_FUNCTION(NULL, "imagesavealpha", NULL, mask, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&newimage, this_ptr, "_create", NULL, _3, _4);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "imagesavealpha", NULL, newimage, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_LONG(&_5, 0);
	ZEPHIR_SINIT_VAR(_6);
	ZVAL_LONG(&_6, 0);
	ZEPHIR_SINIT_VAR(_7);
	ZVAL_LONG(&_7, 0);
	ZEPHIR_SINIT_VAR(_8);
	ZVAL_LONG(&_8, 127);
	ZEPHIR_CALL_FUNCTION(&color, "imagecolorallocatealpha", &_9, newimage, &_5, &_6, &_7, &_8);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_10);
	ZVAL_LONG(_10, 0);
	ZEPHIR_INIT_VAR(_11);
	ZVAL_LONG(_11, 0);
	ZEPHIR_CALL_FUNCTION(NULL, "imagefill", NULL, newimage, _10, _11, color);
	zephir_check_call_status();
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
	_13 = !ZEPHIR_IS_LONG(_12, mask_width);
	if (!(_13)) {
		_14 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
		_13 = !ZEPHIR_IS_LONG(_14, mask_height);
	}
	if (_13) {
		_15 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		_16 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&tempImage, "imagecreatetruecolor", NULL, _15, _16);
		zephir_check_call_status();
		_17 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		_18 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
		ZEPHIR_INIT_BNVAR(_10);
		ZVAL_LONG(_10, 0);
		ZEPHIR_INIT_BNVAR(_11);
		ZVAL_LONG(_11, 0);
		ZEPHIR_INIT_VAR(_19);
		ZVAL_LONG(_19, 0);
		ZEPHIR_INIT_VAR(_20);
		ZVAL_LONG(_20, 0);
		ZEPHIR_INIT_VAR(_21);
		ZVAL_LONG(_21, mask_width);
		ZEPHIR_INIT_VAR(_22);
		ZVAL_LONG(_22, mask_height);
		ZEPHIR_CALL_FUNCTION(NULL, "imagecopyresampled", NULL, tempImage, maskImage, _10, _11, _19, _20, _17, _18, _21, _22);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, maskImage);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(maskImage, tempImage);
	}
	x = 0;
	while (1) {
		_15 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		if (!(ZEPHIR_GT_LONG(_15, x))) {
			break;
		}
		y = 0;
		while (1) {
			_16 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
			if (!(ZEPHIR_GT_LONG(_16, y))) {
				break;
			}
			ZEPHIR_SINIT_NVAR(_5);
			ZVAL_LONG(&_5, x);
			ZEPHIR_SINIT_NVAR(_6);
			ZVAL_LONG(&_6, y);
			ZEPHIR_CALL_FUNCTION(&index, "imagecolorat", &_23, maskImage, &_5, &_6);
			zephir_check_call_status();
			ZEPHIR_CALL_FUNCTION(&color, "imagecolorsforindex", &_24, maskImage, index);
			zephir_check_call_status();
			if (zephir_array_isset_string(color, SS("red"))) {
				zephir_array_fetch_string(&_25, alpha, SL("red"), PH_NOISY | PH_READONLY TSRMLS_CC);
				_26 = (127 - ((zephir_get_numberval(_25) / 2)));
				ZEPHIR_INIT_NVAR(alpha);
				ZVAL_LONG(alpha, _26);
			}
			_17 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_SINIT_NVAR(_5);
			ZVAL_LONG(&_5, x);
			ZEPHIR_SINIT_NVAR(_6);
			ZVAL_LONG(&_6, y);
			ZEPHIR_CALL_FUNCTION(&index, "imagecolorat", &_23, _17, &_5, &_6);
			zephir_check_call_status();
			_18 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_CALL_FUNCTION(&color, "imagecolorsforindex", &_24, _18, index);
			zephir_check_call_status();
			zephir_array_fetch_string(&_25, color, SL("red"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_fetch_string(&_27, color, SL("green"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_fetch_string(&_28, color, SL("blue"), PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&color, "imagecolorallocatealpha", &_9, newimage, _25, _27, _28, alpha);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_10);
			ZVAL_LONG(_10, x);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_LONG(_11, y);
			ZEPHIR_CALL_FUNCTION(NULL, "imagesetpixel", NULL, newimage, _10, _11, color);
			zephir_check_call_status();
			y++;
		}
		x++;
	}
	_15 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _15);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, maskImage);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_image"), newimage TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _background) {

	zval *r_param = NULL, *g_param = NULL, *b_param = NULL, *opacity_param = NULL, *background = NULL, *color = NULL, *_0, *_1, _2, _3, _4, _5, *_6, *_7, *_8, *_9, *_10, *_11, *_12, *_13 = NULL, *_14;
	int r, g, b, opacity, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &r_param, &g_param, &b_param, &opacity_param);

	r = zephir_get_intval(r_param);
	g = zephir_get_intval(g_param);
	b = zephir_get_intval(b_param);
	opacity = zephir_get_intval(opacity_param);


	opacity = ((((opacity * 127) / 100)) - 127);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&background, this_ptr, "_create", NULL, _0, _1);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, r);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, g);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_LONG(&_4, b);
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_LONG(&_5, opacity);
	ZEPHIR_CALL_FUNCTION(&color, "imagecolorallocatealpha", NULL, background, &_2, &_3, &_4, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "imagealphablending", NULL, background, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_9);
	ZVAL_LONG(_9, 0);
	ZEPHIR_INIT_VAR(_10);
	ZVAL_LONG(_10, 0);
	ZEPHIR_INIT_VAR(_11);
	ZVAL_LONG(_11, 0);
	ZEPHIR_INIT_VAR(_12);
	ZVAL_LONG(_12, 0);
	ZEPHIR_CALL_FUNCTION(&_13, "imagecopy", NULL, background, _6, _9, _10, _11, _12, _7, _8);
	zephir_check_call_status();
	if (zephir_is_true(_13)) {
		_14 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, _14);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_image"), background TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _blur) {

	zval *radius_param = NULL, *_0, *_1 = NULL;
	int radius, i, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &radius_param);

	radius = zephir_get_intval(radius_param);


	i = 0;
	while (1) {
		if (!(i < radius)) {
			break;
		}
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZEPHIR_GET_CONSTANT(_1, "IMG_FILTER_GAUSSIAN_BLUR");
		ZEPHIR_CALL_FUNCTION(NULL, "imagefilter", NULL, _0, _1);
		zephir_check_call_status();
		i++;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _pixelate) {

	zephir_fcall_cache_entry *_5 = NULL;
	zval *amount_param = NULL, *color = NULL, *_0, *_1, *_2, _3 = zval_used_for_init, _4 = zval_used_for_init, *_6, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_10 = NULL;
	int amount, x, y, x1, y1, x2, y2, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &amount_param);

	amount = zephir_get_intval(amount_param);


	x = 0;
	while (1) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_width"), PH_NOISY_CC);
		if (!(ZEPHIR_GT_LONG(_0, x))) {
			break;
		}
		y = 0;
		while (1) {
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("_height"), PH_NOISY_CC);
			if (!(ZEPHIR_GT_LONG(_1, y))) {
				break;
			}
			x1 = (x + (amount / 2));
			y1 = (y + (amount / 2));
			_2 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_SINIT_NVAR(_3);
			ZVAL_LONG(&_3, x1);
			ZEPHIR_SINIT_NVAR(_4);
			ZVAL_LONG(&_4, y1);
			ZEPHIR_CALL_FUNCTION(&color, "imagecolorat", &_5, _2, &_3, &_4);
			zephir_check_call_status();
			x2 = (x + amount);
			y2 = (y + amount);
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_7);
			ZVAL_LONG(_7, x1);
			ZEPHIR_INIT_NVAR(_8);
			ZVAL_LONG(_8, y1);
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_LONG(_9, x2);
			ZEPHIR_INIT_NVAR(_10);
			ZVAL_LONG(_10, y2);
			ZEPHIR_CALL_FUNCTION(NULL, "imagefilledrectangle", NULL, _6, _7, _8, _9, _10, color);
			zephir_check_call_status();
			y += amount;
		}
		x += amount;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _save) {

	zend_bool _9;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL, *_3 = NULL, *_6 = NULL, *_8 = NULL;
	int quality, ZEPHIR_LAST_CALL_STATUS;
	zval *file_param = NULL, *quality_param = NULL, *ext = NULL, _0 = zval_used_for_init, *_2 = NULL, *_4, *_5 = NULL, *_7, *_10 = NULL, *_11 = NULL, *_12, *_13, *_14;
	zval *file = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &file_param, &quality_param);

	zephir_get_strval(file, file_param);
	quality = zephir_get_intval(quality_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, 4);
	ZEPHIR_CALL_FUNCTION(&ext, "pathinfo", &_1, file, &_0);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_STRING(&_0, "gif", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "strcasecmp", &_3, ext, &_0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_2, 0)) {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 1);
		zephir_update_property_this(this_ptr, SL("_type"), _4 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_type"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_5, "image_type_to_mime_type", &_6, _4);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_mime"), _5 TSRMLS_CC);
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagegif", NULL, _7, file);
		zephir_check_call_status();
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_STRING(&_0, "jpg", 0);
	ZEPHIR_CALL_FUNCTION(&_5, "strcmp", &_8, ext, &_0);
	zephir_check_call_status();
	_9 = ZEPHIR_IS_LONG(_5, 0);
	if (!(_9)) {
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_STRING(&_0, "jpeg", 0);
		ZEPHIR_CALL_FUNCTION(&_10, "strcmp", &_8, ext, &_0);
		zephir_check_call_status();
		_9 = ZEPHIR_IS_LONG(_10, 0);
	}
	if (_9) {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 2);
		zephir_update_property_this(this_ptr, SL("_type"), _4 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_type"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_11, "image_type_to_mime_type", &_6, _4);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_mime"), _11 TSRMLS_CC);
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_12);
		ZVAL_LONG(_12, quality);
		ZEPHIR_CALL_FUNCTION(NULL, "imagejpeg", NULL, _7, file, _12);
		zephir_check_call_status();
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_STRING(&_0, "png", 0);
	ZEPHIR_CALL_FUNCTION(&_5, "strcmp", &_8, ext, &_0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_5, 0)) {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 3);
		zephir_update_property_this(this_ptr, SL("_type"), _4 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_type"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_11, "image_type_to_mime_type", &_6, _4);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_mime"), _11 TSRMLS_CC);
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagejpeg", NULL, _7, file);
		zephir_check_call_status();
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_STRING(&_0, "wbmp", 0);
	ZEPHIR_CALL_FUNCTION(&_5, "strcmp", &_8, ext, &_0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_5, 0)) {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 15);
		zephir_update_property_this(this_ptr, SL("_type"), _4 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_type"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_11, "image_type_to_mime_type", &_6, _4);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_mime"), _11 TSRMLS_CC);
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagewbmp", NULL, _7, file);
		zephir_check_call_status();
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_STRING(&_0, "xbm", 0);
	ZEPHIR_CALL_FUNCTION(&_5, "strcmp", &_8, ext, &_0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_5, 0)) {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 16);
		zephir_update_property_this(this_ptr, SL("_type"), _4 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_type"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_11, "image_type_to_mime_type", &_6, _4);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_mime"), _11 TSRMLS_CC);
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagexbm", NULL, _7, file);
		zephir_check_call_status();
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_INIT_VAR(_13);
	object_init_ex(_13, phalcon_image_exception_ce);
	ZEPHIR_INIT_VAR(_14);
	ZEPHIR_CONCAT_SVS(_14, "Installed GD does not support '", ext, "' images");
	ZEPHIR_CALL_METHOD(NULL, _13, "__construct", NULL, _14);
	zephir_check_call_status();
	zephir_throw_exception(_13 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _render) {

	zend_bool _8;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_3 = NULL, *_5 = NULL, *_7 = NULL;
	int quality, ZEPHIR_LAST_CALL_STATUS;
	zval *ext_param = NULL, *quality_param = NULL, _1 = zval_used_for_init, *_2 = NULL, *_4, *_6 = NULL, *_9 = NULL, *_10, *_11 = NULL, *_12 = NULL, *_13 = NULL, *_14;
	zval *ext = NULL, *_15;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &ext_param, &quality_param);

	zephir_get_strval(ext, ext_param);
	quality = zephir_get_intval(quality_param);


	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", &_0);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "gif", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "strcasecmp", &_3, ext, &_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_2, 0)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagegif", NULL, _4);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", &_5);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "jpg", 0);
	ZEPHIR_CALL_FUNCTION(&_6, "strcmp", &_7, ext, &_1);
	zephir_check_call_status();
	_8 = ZEPHIR_IS_LONG(_6, 0);
	if (!(_8)) {
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_STRING(&_1, "jpeg", 0);
		ZEPHIR_CALL_FUNCTION(&_9, "strcmp", &_7, ext, &_1);
		zephir_check_call_status();
		_8 = ZEPHIR_IS_LONG(_9, 0);
	}
	if (_8) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_10);
		ZVAL_LONG(_10, quality);
		ZEPHIR_CALL_FUNCTION(NULL, "imagejpeg", NULL, _4, ZEPHIR_GLOBAL(global_null), _10);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", &_5);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "png", 0);
	ZEPHIR_CALL_FUNCTION(&_11, "strcmp", &_7, ext, &_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_11, 0)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagejpeg", NULL, _4);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", &_5);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "wbmp", 0);
	ZEPHIR_CALL_FUNCTION(&_12, "strcmp", &_7, ext, &_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_12, 0)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagewbmp", NULL, _4);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", &_5);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "xbm", 0);
	ZEPHIR_CALL_FUNCTION(&_13, "strcmp", &_7, ext, &_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_13, 0)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_image"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "imagexbm", NULL, _4, ZEPHIR_GLOBAL(global_null));
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", &_5);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_14);
	object_init_ex(_14, phalcon_image_exception_ce);
	ZEPHIR_INIT_VAR(_15);
	ZEPHIR_CONCAT_SVS(_15, "Installed GD does not support '", ext, "' images");
	ZEPHIR_CALL_METHOD(NULL, _14, "__construct", NULL, _15);
	zephir_check_call_status();
	zephir_throw_exception(_14 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, _create) {

	zval *width_param = NULL, *height_param = NULL, *image = NULL, *_0, *_1;
	int width, height, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &width_param, &height_param);

	width = zephir_get_intval(width_param);
	height = zephir_get_intval(height_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, width);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, height);
	ZEPHIR_CALL_FUNCTION(&image, "imagecreatetruecolor", NULL, _0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "imagealphablending", NULL, image, ZEPHIR_GLOBAL(global_false));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "imagesavealpha", NULL, image, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	RETURN_CCTOR(image);

}

PHP_METHOD(Phalcon_Image_Adapter_Gd, __destruct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *image;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(image);
	zephir_read_property_this(&image, this_ptr, SL("_image"), PH_NOISY_CC);
	if (Z_TYPE_P(image) == IS_RESOURCE) {
		ZEPHIR_CALL_FUNCTION(NULL, "imagedestroy", NULL, image);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}
