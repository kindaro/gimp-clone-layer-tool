/* clone-layer tool - plugin for GIMP * /

/*
 * initDialogVals.c
 *
 *  Created on: 5 июля 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

#include "dialog.h"

void initDialogVals(){
	//Rotation values:
	//////////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjAngle),RINT(pl_vals.angle));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRandomAngleFrom),RINT(pl_vals.random_angle_from));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRandomAngleTo),RINT(pl_vals.random_angle_to));
	gimp_scale_entry_set_sensitive(adjRandomAngleFrom,GTK_ADJUSTMENT(adjAngle)->value==0);
	gimp_scale_entry_set_sensitive(adjRandomAngleTo,GTK_ADJUSTMENT(adjAngle)->value==0);

	if(pl_vals.rotate_corner_type == TOP_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbRotateTopLeft), TRUE);
	else if(pl_vals.rotate_corner_type == TOP_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbRotateTopRight), TRUE);
	else if(pl_vals.rotate_corner_type == BOTTOM_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbRotateBottomLeft), TRUE);
	else if(pl_vals.rotate_corner_type == BOTTOM_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbRotateBottomRight), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbRotateCenter), TRUE);

	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordX),RINT(pl_vals.pX));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordY),RINT(pl_vals.pY));

	if(pl_vals.rotate_coord_type == FIXED)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbRotateFixed), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbRotateDinamically), TRUE);

	//Move values:
	//////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjStepX),RINT(pl_vals.step_x));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjStepY),RINT(pl_vals.step_y));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepXMin),RINT(pl_vals.ran_step_x_min));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepXMax),RINT(pl_vals.ran_step_x_max));
	gtk_widget_set_sensitive(spbRanStepXMin, GTK_ADJUSTMENT(adjStepX)->value==0);
	gtk_widget_set_sensitive(spbRanStepXMax, GTK_ADJUSTMENT(adjStepX)->value==0);
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepYMin),RINT(pl_vals.ran_step_y_min));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepYMax),RINT(pl_vals.ran_step_y_max));
	gtk_widget_set_sensitive(spbRanStepYMin, GTK_ADJUSTMENT(adjStepY)->value==0);
	gtk_widget_set_sensitive(spbRanStepYMax, GTK_ADJUSTMENT(adjStepY)->value==0);
	//
	if(pl_vals.start_corner_type == TOP_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbCornerTopLeft), TRUE);
	else if(pl_vals.start_corner_type == TOP_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbCornerTopRight), TRUE);
	else if(pl_vals.start_corner_type == BOTTOM_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbCornerBottomLeft), TRUE);
	else if(pl_vals.start_corner_type == BOTTOM_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbCornerBottomRight), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbCornerCenter), TRUE);
	//
	if(pl_vals.end_corner_type == TOP_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbEndCornerTopLeft), TRUE);
	else if(pl_vals.end_corner_type == TOP_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbEndCornerTopRight), TRUE);
	else if(pl_vals.end_corner_type == BOTTOM_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbEndCornerBottomLeft), TRUE);
	else if(pl_vals.end_corner_type == BOTTOM_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbEndCornerBottomRight), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbEndCornerCenter), TRUE);


	//Scale (resize) values:
	////////////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjStepWidth),RINT(pl_vals.step_width));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjStepHeight),RINT(pl_vals.step_height));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepWidthMin),RINT(pl_vals.ran_step_width_min));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepWidthMax),RINT(pl_vals.ran_step_width_max));
	gtk_widget_set_sensitive(spbRanStepWidthMax, GTK_ADJUSTMENT(adjStepWidth)->value==0);
	gtk_widget_set_sensitive(spbRanStepWidthMin, GTK_ADJUSTMENT(adjStepWidth)->value==0);
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepHeightMin),RINT(pl_vals.ran_step_height_min));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepHeightMax),RINT(pl_vals.ran_step_height_max));
	gtk_widget_set_sensitive(spbRanStepHeightMax, GTK_ADJUSTMENT(adjStepHeight)->value==0);
	gtk_widget_set_sensitive(spbRanStepHeightMin, GTK_ADJUSTMENT(adjStepHeight)->value==0);
	//
	if(pl_vals.resize_type == TOP_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbResizeTopLeft), TRUE);
	else if(pl_vals.resize_type == TOP_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbResizeTopRight), TRUE);
	else if(pl_vals.resize_type == BOTTOM_LEFT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbResizeBottomLeft), TRUE);
	else if(pl_vals.resize_type == BOTTOM_RIGHT)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbResizeBottomRight), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbResizeCenter), TRUE);
	//
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chkAspectRatio), pl_vals.keep_aspect);

	//Opacity values:
	//////////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjAlphaStep),RINT(pl_vals.opacity));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepAlphaMin),RINT(pl_vals.ran_step_opacity_min));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanStepAlphaMax),RINT(pl_vals.ran_step_opacity_max));
	gtk_widget_set_sensitive(spbRanStepAlphaMax, GTK_ADJUSTMENT(adjAlphaStep)->value==0);
	gtk_widget_set_sensitive(spbRanStepAlphaMin, GTK_ADJUSTMENT(adjAlphaStep)->value==0);

	//Blur values:
	//////////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjBlurRadius),RINT(pl_vals.blur_radius));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanBlurMin),RINT(pl_vals.random_blur_min));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanBlurMax),RINT(pl_vals.random_blur_max));
	gtk_widget_set_sensitive(spbRanBlurMax, GTK_ADJUSTMENT(adjBlurRadius)->value==0);
	gtk_widget_set_sensitive(spbRanBlurMin, GTK_ADJUSTMENT(adjBlurRadius)->value==0);

	//Colorize values:
	//////////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjColorizeHue),RINT(pl_vals.colorize_hue));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanHueMin),RINT(pl_vals.random_hue_min));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanHueMax),RINT(pl_vals.random_hue_max));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjColorizeLight),RINT(pl_vals.colorize_light));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjColorizeSat),RINT(pl_vals.colorize_sat));
	gtk_widget_set_sensitive(spbRanHueMin, GTK_ADJUSTMENT(adjColorizeHue)->value==0);
	gtk_widget_set_sensitive(spbRanHueMax, GTK_ADJUSTMENT(adjColorizeHue)->value==0);

	//Noise Spead values:
	//////////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjSpreadSize),RINT(pl_vals.spread_radius));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanSpreadMax),RINT(pl_vals.random_spread_max));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRanSpreadMin),RINT(pl_vals.random_spread_min));
	gtk_widget_set_sensitive(spbRanSpreadMax, GTK_ADJUSTMENT(adjSpreadSize)->value==0);
	gtk_widget_set_sensitive(spbRanSpreadMin, GTK_ADJUSTMENT(adjSpreadSize)->value==0);

	//Animation
	//////////////////////////////////////
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chkEnableAnimate),(gboolean)pl_vals.animate_enable);
	gtk_widget_set_sensitive(frameAnimate, pl_vals.animate_enable);
	gtk_combo_box_set_active(GTK_COMBO_BOX(cmbFirstLayer),pl_vals.anim_tf);
	gtk_combo_box_set_active(GTK_COMBO_BOX(cmbNextLayer),pl_vals.anim_tn);
	gtk_combo_box_set_active(GTK_COMBO_BOX(cmbLastLayer),pl_vals.anim_tl);
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjFirstLayer),RINT(pl_vals.anim_fl));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjNextLayer),RINT(pl_vals.anim_nl));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjLastLayer),RINT(pl_vals.anim_ll));

	//Main clone values:
	/////////////////////////
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjTimes),RINT(pl_vals.times));
	//
	gimp_int_combo_box_set_active(sltInterpolation, pl_vals.interpolation);
	gimp_context_set_interpolation(pl_vals.interpolation);
	//
	if(pl_vals.result_layes == MERGE_LAYERS)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbOneLayer), TRUE);
	else if(pl_vals.result_layes == GROUPING_LAYERS)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbGroupLayer), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbEachLayer), TRUE);
	//
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chkAutocrop), pl_vals.is_autocrop);

	if(pl_vals.layer_order == UP_DOWN_ORDER)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbOrderLayerUp), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbOrderLayerDown), TRUE);
	//
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chkAddBackGround), pl_vals.add_bg);
	gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(cmbBGType),
				pl_vals.add_bg?GTK_SENSITIVITY_ON:GTK_SENSITIVITY_OFF);
	//
	gtk_combo_box_set_active(GTK_COMBO_BOX(cmbBGType),
			((gint)pl_vals.add_bg_type>3 || (gint)pl_vals.add_bg_type<0)?0:(gint)pl_vals.add_bg_type);
}
