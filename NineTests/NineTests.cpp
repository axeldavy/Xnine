/*
 * Copyright 2005, 2007-2008 Henri Verbeet
 * Copyright (C) 2007-2013 Stefan DÃ¶singer(for CodeWeavers)
 * Copyright (C) 2008 Jason Green(for TransGaming)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* These tests are directly adapted from wine d3d9 tests, thanks to the original authors.
 * The code was modified in 2016 */

#include <math.h>
extern "C" {
#include <d3d9.h>
}
#include "Xnine.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "visual.h"

TEST(Xnine, sanity){
    test_sanity();
};
TEST(Xnine, depth_clamp){
    depth_clamp_test();
};
TEST(Xnine, stretchrect){
    stretchrect_test();
};
TEST(Xnine, lighting){
    lighting_test();
};
TEST(Xnine, specular_lighting){
    test_specular_lighting();
};
TEST(Xnine, clear_different_size_surfaces){
    test_clear_different_size_surfaces();
};
TEST(Xnine, color_fill){
    color_fill_test();
};
TEST(Xnine, fog){
    fog_test();
};
TEST(Xnine, cube_wrap){
    test_cube_wrap();
};
TEST(Xnine, z_range){
    z_range_test();
};
TEST(Xnine, multisample_stretch_rect){
    test_multisample_stretch_rect();
};
TEST(Xnine, maxmip){
    maxmip_test();
};
TEST(Xnine, offscreen){
    offscreen_test();
};
TEST(Xnine, ds_size){
    ds_size_test();
};
TEST(Xnine, blend){
    test_blend();
};
TEST(Xnine, shademode){
    test_shademode();
};
TEST(Xnine, srgbtexture){
    srgbtexture_test();
};
TEST(Xnine, release_buffer){
    release_buffer_test();
};
TEST(Xnine, float_texture){
    float_texture_test();
};
TEST(Xnine, g16r16_texture){
    g16r16_texture_test();
};
TEST(Xnine, pixelshader_blending){
    pixelshader_blending_test();
};
TEST(Xnine, texture_transform_flags){
    texture_transform_flags_test();
};
TEST(Xnine, fixed_function_decl){
    fixed_function_decl_test();
};
TEST(Xnine, conditional_np2_repeat){
    conditional_np2_repeat_test();
};
TEST(Xnine, fixed_function_bumpmap){
    fixed_function_bumpmap_test();
};
TEST(Xnine, tssargtemp){
    tssargtemp_test();
};
TEST(Xnine, np2_stretch_rect){
    np2_stretch_rect_test();
};
TEST(Xnine, yuv_color){
    yuv_color_test();
};
TEST(Xnine, yuv_layout){
    yuv_layout_test();
};
TEST(Xnine, zwriteenable){
    zwriteenable_test();
};
TEST(Xnine, alpha){
    alphatest_test();
};
TEST(Xnine, viewport){
    test_viewport();
};
TEST(Xnine, generate_mipmap){
    test_generate_mipmap();
};
TEST(Xnine, mipmap_autogen){
    test_mipmap_autogen();
};
TEST(Xnine, constant_clamp_vs){
    test_constant_clamp_vs();
};
TEST(Xnine, compare_instructions){
    test_compare_instructions();
};
TEST(Xnine, mova){
    test_mova();
};
TEST(Xnine, sincos){
    sincos_test();
};
TEST(Xnine, loop_index){
    loop_index_test();
};
TEST(Xnine, sgn){
    sgn_test();
};
TEST(Xnine, clip_planes){
    clip_planes_test();
};
TEST(Xnine, vshader_input){
    test_vshader_input();
};
TEST(Xnine, vshader_float16){
    test_vshader_float16();
};
TEST(Xnine, stream){
    stream_test();
};
TEST(Xnine, fog_with_shader){
    fog_with_shader_test();
};
TEST(Xnine, texbem){
    texbem_test();
};
TEST(Xnine, texdepth){
    texdepth_test();
};
TEST(Xnine, texkill){
    texkill_test();
};
TEST(Xnine, volume_v16u16){
    volume_v16u16_test();
};
TEST(Xnine, constant_clamp_ps){
    constant_clamp_ps_test();
};
TEST(Xnine, cnd){
    cnd_test();
};
TEST(Xnine, dp2add_ps){
    dp2add_ps_test();
};
TEST(Xnine, unbound_sampler){
    unbound_sampler_test();
};
TEST(Xnine, nested_loop){
    nested_loop_test();
};
TEST(Xnine, pretransformed_varying){
    pretransformed_varying_test();
};
TEST(Xnine, vface_register){
    vface_register_test();
};
TEST(Xnine, fragment_coords){
    test_fragment_coords();
};
TEST(Xnine, multiple_rendertargets){
    multiple_rendertargets_test();
};
TEST(Xnine, texop){
    texop_test();
};
TEST(Xnine, texop_range){
    texop_range_test();
};
TEST(Xnine, alphareplicate){
    alphareplicate_test();
};
TEST(Xnine, dp3_alpha){
    dp3_alpha_test();
};
TEST(Xnine, depth_buffer){
    depth_buffer_test();
};
TEST(Xnine, depth_buffer2){
    depth_buffer2_test();
};
TEST(Xnine, depth_blit){
    depth_blit_test();
};
TEST(Xnine, intz){
    intz_test();
};
TEST(Xnine, shadow){
    shadow_test();
};
TEST(Xnine, fp_special){
    fp_special_test();
};
TEST(Xnine, depth_bounds){
    depth_bounds_test();
};
TEST(Xnine, srgbwrite_format){
    srgbwrite_format_test();
};
TEST(Xnine, update_surface){
    update_surface_test();
};
TEST(Xnine, multisample_get_rtdata){
    multisample_get_rtdata_test();
};
TEST(Xnine, multisample_get_front_buffer_data){
    test_multisample_get_front_buffer_data();
};
TEST(Xnine, zenable){
    zenable_test();
};
TEST(Xnine, fog_special){
    fog_special_test();
};
TEST(Xnine, volume_srgb){
    volume_srgb_test();
};
TEST(Xnine, volume_dxtn){
    volume_dxtn_test();
};
TEST(Xnine, add_dirty_rect){
    add_dirty_rect_test();
};
TEST(Xnine, multisampled_depth_buffer){
    multisampled_depth_buffer_test();
};
TEST(Xnine, resz){
    resz_test();
};
TEST(Xnine, stencil_cull){
    stencil_cull_test();
};
TEST(Xnine, buffer_no_dirty_update){
    test_buffer_no_dirty_update();
};
TEST(Xnine, per_stage_constant){
    test_per_stage_constant();
};
TEST(Xnine, 3dc_formats){
    test_3dc_formats();
};
TEST(Xnine, fog_interpolation){
    test_fog_interpolation();
};
TEST(Xnine, negative_fixedfunction_fog){
    test_negative_fixedfunction_fog();
};
TEST(Xnine, position_index){
    test_position_index();
};
TEST(Xnine, table_fog_zw){
    test_table_fog_zw();
};
TEST(Xnine, signed_formats){
    test_signed_formats();
};
TEST(Xnine, multisample_mismatch){
    test_multisample_mismatch();
};
TEST(Xnine, texcoordindex){
    test_texcoordindex();
};
TEST(Xnine, vertex_blending){
    test_vertex_blending();
};
TEST(Xnine, updatetexture){
    test_updatetexture();
};
TEST(Xnine, depthbias){
    test_depthbias();
};
TEST(Xnine, flip){
    test_flip();
};
TEST(Xnine, uninitialized_varyings){
    test_uninitialized_varyings();
};
TEST(Xnine, multisample_init){
    test_multisample_init();
};
TEST(Xnine, depth_stencil_init){
    test_depth_stencil_init();
};
TEST(Xnine, texture_blending){
    test_texture_blending();
};
TEST(Xnine, color_clamping){
    test_color_clamping();
};
TEST(Xnine, line_antialiasing_blending){
    test_line_antialiasing_blending();
};
TEST(Xnine, dsy){
    test_dsy();
};
TEST(Xnine, evict_bound_resources){
    test_evict_bound_resources();
};
TEST(Xnine, max_index16){
    test_max_index16();
};
TEST(Xnine, backbuffer_resize){
    test_backbuffer_resize();
};
TEST(Xnine, drawindexedprimitiveup){
    test_drawindexedprimitiveup();
};
TEST(Xnine, vertex_texture){
    test_vertex_texture();
};
TEST(Xnine, mvp_software_vertex_shaders){
    test_mvp_software_vertex_shaders();
};
TEST(Xnine, null_format){
    test_null_format();
};
TEST(Xnine, color_vertex){
    test_color_vertex();
};
TEST(Xnine, sysmem_draw){
    test_sysmem_draw();
};
TEST(Xnine, nrm_instruction){
    test_nrm_instruction();
};
TEST(Xnine, mismatched_sample_types){
    test_mismatched_sample_types();
};
TEST(Xnine, draw_mapped_buffer){
    test_draw_mapped_buffer();
};
TEST(Xnine, alpha_to_coverage){
    test_alpha_to_coverage();
};
TEST(Xnine, sample_mask){
    test_sample_mask();
};
TEST(Xnine, dynamic_map_synchronization){
    test_dynamic_map_synchronization();
};
TEST(Xnine, filling_convention){
    test_filling_convention();
};
TEST(Xnine, managed_reset){
    test_managed_reset();
};
TEST(Xnine, managed_generate_mipmap){
    test_managed_generate_mipmap();
};

class TestEnvironment : public ::testing::Environment {
    virtual void SetUp() {
        if (!Xnine_init(-1, &priv)) {
            printf("Failed to initialize Xnine\n");
            return 0;
        }
    }

    virtual void TearDown() {
        Xnine_close(priv);
    }
};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}
