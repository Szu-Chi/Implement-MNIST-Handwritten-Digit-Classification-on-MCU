/**
  ******************************************************************************
  * @file    digit_cnn.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Thu Jul 28 17:34:33 2022
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "digit_cnn.h"
#include "digit_cnn_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_digit_cnn
 
#undef AI_DIGIT_CNN_MODEL_SIGNATURE
#define AI_DIGIT_CNN_MODEL_SIGNATURE     "54635afde218fca73d0a831103c6dd5c"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Thu Jul 28 17:34:33 2022"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_DIGIT_CNN_N_BATCHES
#define AI_DIGIT_CNN_N_BATCHES         (1)

static ai_ptr g_digit_cnn_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_digit_cnn_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_1_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 144, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  dense_dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 200, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  dense_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1440, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  dense_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  input_1_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 28, 28), AI_STRIDE_INIT(4, 4, 4, 4, 112),
  1, &input_1_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_conv2d_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 8, 8), AI_STRIDE_INIT(4, 4, 4, 32, 256),
  1, &conv2d_conv2d_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_conv2d_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 3, 3), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &conv2d_1_conv2d_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_conv2d_output0, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 144, 1, 1), AI_STRIDE_INIT(4, 4, 4, 576, 576),
  1, &conv2d_1_conv2d_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_dense_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_dense_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  dense_output, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_conv2d_weights, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 5, 8), AI_STRIDE_INIT(4, 4, 4, 20, 100),
  1, &conv2d_conv2d_weights_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_conv2d_bias, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_conv2d_bias_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_conv2d_weights, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 8, 3, 3, 16), AI_STRIDE_INIT(4, 4, 32, 96, 288),
  1, &conv2d_1_conv2d_weights_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_conv2d_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_1_conv2d_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  dense_dense_weights, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 144, 10, 1, 1), AI_STRIDE_INIT(4, 4, 576, 5760, 5760),
  1, &dense_dense_weights_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  dense_dense_bias, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_dense_bias_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_layer, 4,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm,
  &dense_chain,
  NULL, &dense_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_conv2d_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_dense_weights, &dense_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_dense_layer, 4,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_dense_chain,
  NULL, &dense_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_conv2d_weights, &conv2d_1_conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_conv2d_layer, 2,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &conv2d_1_conv2d_chain,
  NULL, &dense_dense_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_conv2d_weights, &conv2d_conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_conv2d_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &conv2d_conv2d_chain,
  NULL, &conv2d_1_conv2d_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(3, 3), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 11304, 1, 1),
    11304, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 3536, 1, 1),
    3536, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_DIGIT_CNN_IN_NUM, &input_1_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_DIGIT_CNN_OUT_NUM, &dense_output),
  &conv2d_conv2d_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 11304, 1, 1),
      11304, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 3536, 1, 1),
      3536, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_DIGIT_CNN_IN_NUM, &input_1_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_DIGIT_CNN_OUT_NUM, &dense_output),
  &conv2d_conv2d_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool digit_cnn_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_digit_cnn_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_1_output_array.data = AI_PTR(g_digit_cnn_activations_map[0] + 400);
    input_1_output_array.data_start = AI_PTR(g_digit_cnn_activations_map[0] + 400);
    
    conv2d_conv2d_output_array.data = AI_PTR(g_digit_cnn_activations_map[0] + 0);
    conv2d_conv2d_output_array.data_start = AI_PTR(g_digit_cnn_activations_map[0] + 0);
    
    conv2d_1_conv2d_output_array.data = AI_PTR(g_digit_cnn_activations_map[0] + 2048);
    conv2d_1_conv2d_output_array.data_start = AI_PTR(g_digit_cnn_activations_map[0] + 2048);
    
    dense_dense_output_array.data = AI_PTR(g_digit_cnn_activations_map[0] + 0);
    dense_dense_output_array.data_start = AI_PTR(g_digit_cnn_activations_map[0] + 0);
    
    dense_output_array.data = AI_PTR(g_digit_cnn_activations_map[0] + 40);
    dense_output_array.data_start = AI_PTR(g_digit_cnn_activations_map[0] + 40);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool digit_cnn_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_digit_cnn_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_conv2d_weights_array.data = AI_PTR(g_digit_cnn_weights_map[0] + 0);
    conv2d_conv2d_weights_array.data_start = AI_PTR(g_digit_cnn_weights_map[0] + 0);
    
    conv2d_conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_conv2d_bias_array.data = AI_PTR(g_digit_cnn_weights_map[0] + 800);
    conv2d_conv2d_bias_array.data_start = AI_PTR(g_digit_cnn_weights_map[0] + 800);
    
    conv2d_1_conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_conv2d_weights_array.data = AI_PTR(g_digit_cnn_weights_map[0] + 832);
    conv2d_1_conv2d_weights_array.data_start = AI_PTR(g_digit_cnn_weights_map[0] + 832);
    
    conv2d_1_conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_conv2d_bias_array.data = AI_PTR(g_digit_cnn_weights_map[0] + 5440);
    conv2d_1_conv2d_bias_array.data_start = AI_PTR(g_digit_cnn_weights_map[0] + 5440);
    
    dense_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_dense_weights_array.data = AI_PTR(g_digit_cnn_weights_map[0] + 5504);
    dense_dense_weights_array.data_start = AI_PTR(g_digit_cnn_weights_map[0] + 5504);
    
    dense_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_dense_bias_array.data = AI_PTR(g_digit_cnn_weights_map[0] + 11264);
    dense_dense_bias_array.data_start = AI_PTR(g_digit_cnn_weights_map[0] + 11264);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_digit_cnn_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_DIGIT_CNN_MODEL_NAME,
      .model_signature   = AI_DIGIT_CNN_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 25448,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_digit_cnn_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_DIGIT_CNN_MODEL_NAME,
      .model_signature   = AI_DIGIT_CNN_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 25448,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_digit_cnn_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_digit_cnn_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_digit_cnn_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_digit_cnn_create(network, AI_DIGIT_CNN_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_digit_cnn_data_params_get(&params) != true) {
        err = ai_digit_cnn_get_error(*network);
        return err;
    }
#if defined(AI_DIGIT_CNN_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_DIGIT_CNN_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_digit_cnn_init(*network, &params) != true) {
        err = ai_digit_cnn_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_digit_cnn_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_digit_cnn_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_digit_cnn_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_digit_cnn_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= digit_cnn_configure_weights(net_ctx, params);
  ok &= digit_cnn_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_digit_cnn_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_digit_cnn_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_DIGIT_CNN_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

