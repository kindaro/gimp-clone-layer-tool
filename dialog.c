/* clone-layer tool - plugin for GIMP * /

/*
 * dialog.c
 *
 * Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

#include "dialog.h"
#include "initDialogVals.c"

void on_set_add_bg_radio(GtkToggleButton *togglebutton, gpointer none){
	pl_vals.add_bg = (gboolean)GPOINTER_TO_INT(
			gtk_toggle_button_get_active(togglebutton));
	gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(cmbBGType),
			pl_vals.add_bg?GTK_SENSITIVITY_ON:GTK_SENSITIVITY_OFF);
}

void on_set_add_bg_combo(GtkComboBox *combobox, gpointer none){
	gchar *curText = gtk_combo_box_get_active_text(combobox);

	if(strncmp(curText, STR_BG_FILL, 20)==0)
		pl_vals.add_bg_type = ADD_BG_BG;
	else if(strncmp(curText, STR_FG_FILL, 20)==0)
		pl_vals.add_bg_type = ADD_BG_FG;
	else if(strncmp(curText, STR_VIEW_FILL, 20)==0)
			pl_vals.add_bg_type = ADD_BG_VIEW;
}

void on_set_radio(GtkToggleButton *togglebutton, gpointer clone_type){
	pl_vals.clone_type = (enum CLONE_LAYER) GPOINTER_TO_INT(clone_type);
}

void on_set_order_radio(GtkToggleButton *togglebutton, gpointer order_type){
	pl_vals.layer_order = GPOINTER_TO_INT(order_type);
}

void on_set_result_radio(GtkToggleButton *togglebutton, gpointer result_type){
	pl_vals.result_layes = (enum RESULT_LAYERS_TYPE ) GPOINTER_TO_INT(result_type);
}

void on_set_auto_coord_radio(GtkToggleButton *togglebutton, gpointer coord_type){
	LayerData tmpData;
	tmpData = getLayerData(workLayer);

	enum AUTO_COORD_TYPE cType = (enum AUTO_COORD_TYPE) GPOINTER_TO_INT(coord_type);
	pl_vals.rotate_corner_type = cType;

	gint x1 = tmpData.x1;
	gint y1 = tmpData.y1;
	gint x2 = tmpData.x2;
	gint y2 = tmpData.y2;

	gint width = tmpData.w;
	gint height = tmpData.h;

	if(cType == TOP_LEFT){
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordX), (gdouble)x1);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordY), (gdouble)y1);
	}
	else if(cType == TOP_RIGHT){
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordX), (gdouble)x2);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordY), (gdouble)y1);
	}
	else if(cType == BOTTOM_LEFT){
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordX), (gdouble)x1);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordY), (gdouble)y2);
	}
	else if(cType == BOTTOM_RIGHT){
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordX), (gdouble)x2);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordY), (gdouble)y2);
	}
	else {//center - center
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordX), (gdouble)x1+(width/2));
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjManRotateCoordY), (gdouble)y1+(height/2));
	}
}

void on_set_start_corner_radio(GtkToggleButton *togglebutton, gpointer corner_type){
	enum AUTO_COORD_TYPE cType = (enum AUTO_COORD_TYPE) GPOINTER_TO_INT(corner_type);
	pl_vals.start_corner_type = cType;

	if(cType == TOP_LEFT)
			gtk_label_set_text(GTK_LABEL(lbStartCorners),"TOP/LEFT");
		else if(cType == TOP_RIGHT)
			gtk_label_set_text(GTK_LABEL(lbStartCorners),"TOP/RIGHT");
		else if(cType == BOTTOM_LEFT)
			gtk_label_set_text(GTK_LABEL(lbStartCorners),"BOTTOM/LEFT");
		else if(cType == BOTTOM_RIGHT)
			gtk_label_set_text(GTK_LABEL(lbStartCorners),"BOTTOM/RIGHT");
		else
			gtk_label_set_text(GTK_LABEL(lbStartCorners),"CENTER");
}

void on_set_end_corner_radio(GtkToggleButton *togglebutton, gpointer corner_type){
	enum AUTO_COORD_TYPE cType = (enum AUTO_COORD_TYPE) GPOINTER_TO_INT(corner_type);
		pl_vals.end_corner_type = cType;

		if(cType == TOP_LEFT)
					gtk_label_set_text(GTK_LABEL(lbEndCorners),"TOP/LEFT");
				else if(cType == TOP_RIGHT)
					gtk_label_set_text(GTK_LABEL(lbEndCorners),"TOP/RIGHT");
				else if(cType == BOTTOM_LEFT)
					gtk_label_set_text(GTK_LABEL(lbEndCorners),"BOTTOM/LEFT");
				else if(cType == BOTTOM_RIGHT)
					gtk_label_set_text(GTK_LABEL(lbEndCorners),"BOTTOM/RIGHT");
				else
					gtk_label_set_text(GTK_LABEL(lbEndCorners),"CENTER");

}

void on_set_resize_type_radio(GtkToggleButton *togglebutton, gpointer coord_type){
	enum AUTO_COORD_TYPE cType = (enum AUTO_COORD_TYPE) GPOINTER_TO_INT(coord_type);
	pl_vals.resize_type = cType;

	if(cType == TOP_LEFT)
		gtk_label_set_text(GTK_LABEL(lbResizeType),"Resize Direction - TOP/LEFT");
	else if(cType == TOP_RIGHT)
		gtk_label_set_text(GTK_LABEL(lbResizeType),"Resize Direction - TOP/RIGHT");
	else if(cType == BOTTOM_LEFT)
		gtk_label_set_text(GTK_LABEL(lbResizeType),"Resize Direction - BOTTOM/LEFT");
	else if(cType == BOTTOM_RIGHT)
		gtk_label_set_text(GTK_LABEL(lbResizeType),"Resize Direction - BOTTOM/RIGHT");
	else
		gtk_label_set_text(GTK_LABEL(lbResizeType),"Resize Direction - CENTER");
}

void on_set_rotate_coord_radio(GtkToggleButton *togglebutton, gpointer coord_type){
	enum TYPE_ROTATE_COORDINATES cType = (enum TYPE_ROTATE_COORDINATES) GPOINTER_TO_INT(coord_type);
	pl_vals.rotate_coord_type = cType;

	if(cType == DINAMIC){
		gtk_widget_set_sensitive(spbManRotateCoordX, FALSE);
		gtk_widget_set_sensitive(spbManRotateCoordY, FALSE);
	}
	else{
		gtk_widget_set_sensitive(spbManRotateCoordX, TRUE);
		gtk_widget_set_sensitive(spbManRotateCoordY, TRUE);
	}
}

void checkValues(GtkToggleButton *togglebutton, gpointer whatCheck){

	ChkValues check = GPOINTER_TO_INT(whatCheck);

	if(check == CHK_MAX_ANGLE){
		if(GTK_ADJUSTMENT(adjRandomAngleTo)->value<GTK_ADJUSTMENT(adjRandomAngleFrom)->value)
			gtk_adjustment_set_value(GTK_ADJUSTMENT(adjRandomAngleFrom),GTK_ADJUSTMENT(adjRandomAngleTo)->value);
	}
	else if(check == CHK_MIN_ANGLE){
		if(GTK_ADJUSTMENT(adjRandomAngleFrom)->value>GTK_ADJUSTMENT(adjRandomAngleTo)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRandomAngleTo),GTK_ADJUSTMENT(adjRandomAngleFrom)->value
					);
	}


	else if(check == CHK_MIN_STEP_X){
		if(GTK_ADJUSTMENT(adjRanStepXMin)->value>GTK_ADJUSTMENT(adjRanStepXMax)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepXMax),GTK_ADJUSTMENT(adjRanStepXMin)->value
					);
	}
	else if(check == CHK_MAX_STEP_X){
		if(GTK_ADJUSTMENT(adjRanStepXMax)->value<GTK_ADJUSTMENT(adjRanStepXMin)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepXMin),GTK_ADJUSTMENT(adjRanStepXMax)->value
					);
	}
	else if(check == CHK_MIN_STEP_Y){
		if(GTK_ADJUSTMENT(adjRanStepYMin)->value>GTK_ADJUSTMENT(adjRanStepYMax)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepYMax),GTK_ADJUSTMENT(adjRanStepYMin)->value
					);
	}
	else if(check == CHK_MAX_STEP_Y){
		if(GTK_ADJUSTMENT(adjRanStepYMax)->value<GTK_ADJUSTMENT(adjRanStepYMin)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepYMin),GTK_ADJUSTMENT(adjRanStepYMax)->value
					);
	}



	else if(check == CHK_MIN_STEP_W){
		if(GTK_ADJUSTMENT(adjRanStepWidthMin)->value>GTK_ADJUSTMENT(adjRanStepWidthMax)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepWidthMax),GTK_ADJUSTMENT(adjRanStepWidthMin)->value
					);
	}
	else if(check == CHK_MAX_STEP_W){
		if(GTK_ADJUSTMENT(adjRanStepWidthMax)->value<GTK_ADJUSTMENT(adjRanStepWidthMin)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepWidthMin),GTK_ADJUSTMENT(adjRanStepWidthMax)->value
					);
	}
	else if(check == CHK_MIN_STEP_H){
		if(GTK_ADJUSTMENT(adjRanStepHeightMin)->value>GTK_ADJUSTMENT(adjRanStepHeightMax)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepHeightMax),GTK_ADJUSTMENT(adjRanStepHeightMin)->value
					);
	}
	else if(check == CHK_MAX_STEP_H){
		if(GTK_ADJUSTMENT(adjRanStepAlphaMax)->value<GTK_ADJUSTMENT(adjRanStepAlphaMin)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepAlphaMin),GTK_ADJUSTMENT(adjRanStepAlphaMax)->value
					);
	}

	else if(check == CHK_MIN_ALPHA){
		if(GTK_ADJUSTMENT(adjRanStepAlphaMin)->value>GTK_ADJUSTMENT(adjRanStepAlphaMax)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepAlphaMax),GTK_ADJUSTMENT(adjRanStepAlphaMin)->value
					);
	}
	else if(check == CHK_MAX_ALPHA){
		if(GTK_ADJUSTMENT(adjRanStepAlphaMax)->value<GTK_ADJUSTMENT(adjRanStepAlphaMin)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanStepAlphaMin),GTK_ADJUSTMENT(adjRanStepAlphaMax)->value
					);
	}



	else if(check == CHK_ANGLE){
		gimp_scale_entry_set_sensitive(
				adjRandomAngleFrom,
				GTK_ADJUSTMENT(adjAngle)->value==0);
		gimp_scale_entry_set_sensitive(
						adjRandomAngleTo,
						GTK_ADJUSTMENT(adjAngle)->value==0);
	}
	else if(check == CHK_STEP_X){
		gtk_widget_set_sensitive(
				spbRanStepXMin,
					GTK_ADJUSTMENT(adjStepX)->value==0);
		gtk_widget_set_sensitive(
				spbRanStepXMax,
							GTK_ADJUSTMENT(adjStepX)->value==0);
		}
	else if(check == CHK_STEP_Y){
		gtk_widget_set_sensitive(
				spbRanStepYMin,
					GTK_ADJUSTMENT(adjStepY)->value==0);
		gtk_widget_set_sensitive(
				spbRanStepYMax,
							GTK_ADJUSTMENT(adjStepY)->value==0);
		}
	else if(check == CHK_SET_W){
		gtk_widget_set_sensitive(
				spbRanStepWidthMin,
					GTK_ADJUSTMENT(adjStepWidth)->value==0);
		gtk_widget_set_sensitive(
				spbRanStepWidthMax,
							GTK_ADJUSTMENT(adjStepWidth)->value==0);
		}
	else if(check == CHK_SET_H){
		gtk_widget_set_sensitive(
				spbRanStepHeightMin,
					(GTK_ADJUSTMENT(adjStepHeight)->value==0 && !pl_vals.keep_aspect));
		gtk_widget_set_sensitive(
				spbRanStepHeightMax,
							(GTK_ADJUSTMENT(adjStepHeight)->value==0 && !pl_vals.keep_aspect));
		}
	else if(check == CHK_OPACITY){
		gtk_widget_set_sensitive(
				spbRanStepAlphaMin,
					GTK_ADJUSTMENT(adjAlphaStep)->value==0);
		gtk_widget_set_sensitive(
				spbRanStepAlphaMax,
							GTK_ADJUSTMENT(adjAlphaStep)->value==0);
		}

	else if(check == CHK_BLUR){
			gtk_widget_set_sensitive(
					spbRanBlurMin,
						GTK_ADJUSTMENT(adjBlurRadius)->value==0);
			gtk_widget_set_sensitive(
					spbRanBlurMax,
								GTK_ADJUSTMENT(adjBlurRadius)->value==0);
			}
	else if(check == CHK_MAX_BLUR){
			if(GTK_ADJUSTMENT(adjRanBlurMax)->value<GTK_ADJUSTMENT(adjRanBlurMin)->value)
				gtk_adjustment_set_value(
						GTK_ADJUSTMENT(adjRanBlurMin),GTK_ADJUSTMENT(adjRanBlurMax)->value
						);
		}
	else if(check == CHK_MIN_BLUR){
		if(GTK_ADJUSTMENT(adjRanBlurMin)->value>GTK_ADJUSTMENT(adjRanBlurMax)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanBlurMax),GTK_ADJUSTMENT(adjRanBlurMin)->value
					);
	}

	//Colorize
	else if(check == CHK_COLORIZE){
		gtk_widget_set_sensitive(
		spbRanHueMin,
		GTK_ADJUSTMENT(adjColorizeHue)->value==0);
		gtk_widget_set_sensitive(
		spbRanHueMax,
		GTK_ADJUSTMENT(adjColorizeHue)->value==0);
		}
	else if(check == CHK_MAX_HUE){
		if(GTK_ADJUSTMENT(adjRanHueMax)->value<GTK_ADJUSTMENT(adjRanHueMin)->value)
			gtk_adjustment_set_value(
			GTK_ADJUSTMENT(adjRanHueMin),GTK_ADJUSTMENT(adjRanHueMax)->value
			);
	}
	else if(check == CHK_MIN_HUE){
		if(GTK_ADJUSTMENT(adjRanHueMin)->value>GTK_ADJUSTMENT(adjRanHueMax)->value)
			gtk_adjustment_set_value(
					GTK_ADJUSTMENT(adjRanHueMax),GTK_ADJUSTMENT(adjRanHueMin)->value
					);
	}

	//Noise Spread
	/////////////////////////
	else if(check == CHK_SPREAD){
			gtk_widget_set_sensitive(
			spbRanSpreadMin,
			GTK_ADJUSTMENT(adjSpreadSize)->value==0);
			gtk_widget_set_sensitive(
			spbRanSpreadMax,
			GTK_ADJUSTMENT(adjSpreadSize)->value==0);
			}
	else if(check == CHK_MAX_SPREAD){
		if(GTK_ADJUSTMENT(adjRanSpreadMax)->value<GTK_ADJUSTMENT(adjRanSpreadMin)->value)
			gtk_adjustment_set_value(
			GTK_ADJUSTMENT(adjRanSpreadMin),GTK_ADJUSTMENT(adjRanSpreadMax)->value
			);
	}
	else if(check == CHK_MIN_SPREAD){
		if(GTK_ADJUSTMENT(adjRanSpreadMin)->value<GTK_ADJUSTMENT(adjRanSpreadMax)->value)
			gtk_adjustment_set_value(
			GTK_ADJUSTMENT(adjRanSpreadMax),GTK_ADJUSTMENT(adjRanSpreadMin)->value
			);
	}
}

void on_size_changed(GtkToggleButton *togglebutton, gpointer whatCheck){

	ChkValues check = GPOINTER_TO_INT(whatCheck);
	LayerData tmpData = getLayerData(workLayer);

	gdouble curAspect = (gdouble)tmpData.w/(gdouble)tmpData.h;

	if(pl_vals.keep_aspect){
		if(check == CHK_SET_W){
			gtk_adjustment_set_value(GTK_ADJUSTMENT(adjStepHeight),
					GTK_ADJUSTMENT(adjStepWidth)->value/curAspect);
		}
		else if(check == CHK_SET_H){
			gtk_adjustment_set_value(GTK_ADJUSTMENT(adjStepWidth),
								GTK_ADJUSTMENT(adjStepHeight)->value*curAspect);
		}
	}
}

void on_set_aspect_ratio(GtkToggleButton *togglebutton, gpointer none){
	pl_vals.keep_aspect = togglebutton->active;

	if(togglebutton->active){
		gtk_widget_set_sensitive(spbRanStepHeightMin, FALSE);
		gtk_widget_set_sensitive(spbRanStepHeightMax, FALSE);
	}
	else{
		gtk_widget_set_sensitive(spbRanStepHeightMax, TRUE);
		gtk_widget_set_sensitive(spbRanStepHeightMin, TRUE);
	}

}
void on_set_animate_on_radio(GtkToggleButton *togglebutton, gpointer none){
	pl_vals.animate_enable = togglebutton->active;
    gtk_widget_set_sensitive(frameAnimate, pl_vals.animate_enable);
}

void on_set_autocrop_radio(GtkToggleButton *togglebutton, gpointer none){
	pl_vals.is_autocrop = togglebutton->active;
}

void on_set_interpolation_radio(GimpIntComboBox *combo_box, gpointer none){
	gint val;
	GimpInterpolationType iType = GIMP_INTERPOLATION_NONE;
	gimp_int_combo_box_get_active(combo_box, &val);

	if(val == 1) iType = GIMP_INTERPOLATION_LINEAR;
	else if(val == 2) iType = GIMP_INTERPOLATION_CUBIC;
	else if(val == 3) iType = GIMP_INTERPOLATION_LANCZOS;

	pl_vals.interpolation = iType;
	gimp_context_set_interpolation(iType);
}

void on_set_animate_type_combo(GtkComboBox *combo_box, gpointer type){

	const gchar *title = gtk_combo_box_get_title(combo_box);
	gint index = gtk_combo_box_get_active(combo_box);

	if(strcmp(title,STR_ANIM_FIRST)==0)
		pl_vals.anim_tf=index;
	else if(strcmp(title,STR_ANIM_NEXT)==0)
		pl_vals.anim_tn=index;
	else
		pl_vals.anim_tl=index;

}

void onResetVals(){
	LayerData tmpLayer = getLayerData(workLayer);
	initVals();
	pl_vals.pX = tmpLayer.x1+(tmpLayer.w/2);
	pl_vals.pY = tmpLayer.y1+(tmpLayer.h/2);
	initDialogVals();
}

gboolean clone_dialog (void)
{
  GSList *listApplyRadios = NULL; // for radio groups
  GSList *listCloneFrom = NULL;
  GtkWidget *dialog; //GIMP dialog window
  GtkWidget *main_vbox; //Main vert.box
  gboolean   run;

  gimp_ui_init (PLUG_IN_BINARY, FALSE);
  LayerData tmpLayer = getLayerData(workLayer);
  gchar newName[256]="";
  		  sprintf(newName,"CTL-v0.2b (Size - W:%i/H:%i)",tmpLayer.w, tmpLayer.h);

  dialog = gimp_dialog_new (newName, PLUG_IN_ROLE,
                            NULL, 0,
                            gimp_standard_help_func, PLUG_IN_PROC,
                            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                            GTK_STOCK_OK,     GTK_RESPONSE_OK,
                            NULL);

  gtk_window_set_default_size(GTK_WINDOW(dialog),380,620);
  gtk_dialog_set_alternative_button_order (GTK_DIALOG (dialog),
                                           GTK_RESPONSE_OK,
                                           GTK_RESPONSE_CANCEL,
                                           -1);

  gimp_window_set_transient (GTK_WINDOW (dialog));

  //Add GtkVBox with padding - 3px
  main_vbox = gtk_vbox_new (FALSE, 3);
  //Add main_vbox to dialog
  gtk_container_add (GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), main_vbox);
  gtk_widget_show (main_vbox);

  //1.
  //////////////////////////////////////////
  //Add scrolled_window for expander panels
  GtkWidget* scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  gtk_widget_show(scrolledWindow);
  gtk_box_pack_start(GTK_BOX(main_vbox), scrolledWindow, TRUE, TRUE, 0);
  	  //Add viewport to make  a scroll effect!
      GtkWidget* viewport =  gtk_viewport_new (NULL, NULL);
	  gtk_widget_show(viewport);
	  gtk_container_add(GTK_CONTAINER(scrolledWindow), viewport);
	  //Add alignment
	  GtkWidget* alignmentExpander = gtk_alignment_new(
	  		  			  0.5,
	  		  			  0.5,
	  		  			  1,
	  		  			  1);
	  gtk_alignment_set_padding(GTK_ALIGNMENT(alignmentExpander),0,0,6,6);
	  gtk_widget_show(alignmentExpander);
	  gtk_container_add(GTK_CONTAINER(viewport), alignmentExpander);
	  //Add vbox to viewport for the expander panels
	  GtkWidget* vboxExpander = gtk_vbox_new (FALSE, 0);
	  gtk_widget_show(vboxExpander);
	  gtk_container_add(GTK_CONTAINER(alignmentExpander), vboxExpander);

		/////////////////////////////////////////////////////////
		//Add Scale expander panels:
		//////////////////////////////////////////////////////////
		GtkWidget* epResize = gtk_expander_new(
				"<span foreground='#00438A'><b>RESIZE</b></span>"
				);
		gtk_expander_set_use_markup(GTK_EXPANDER(epResize), TRUE);
		gtk_widget_show(epResize);
		gtk_box_pack_start(GTK_BOX(vboxExpander), epResize, FALSE, TRUE, 0);
		//Add alignment
		GtkWidget* alignmentResize = gtk_alignment_new(
				0.5,
				0.5,
				1,
				1);
		gtk_alignment_set_padding(GTK_ALIGNMENT(alignmentResize),0,0,6,6);
		gtk_widget_show(alignmentResize);
		gtk_container_add(GTK_CONTAINER(epResize), alignmentResize);
		//Add vbox for frames
		GtkWidget* vboxResize =  gtk_vbox_new (FALSE, 0);
		gtk_widget_show(vboxResize);
		gtk_container_add(GTK_CONTAINER(alignmentResize), vboxResize);
		//Add frame for Fixed steps
		GtkWidget* frameResizeFixStep = gtk_frame_new("");
		gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameResizeFixStep))),"<b>Fixed Steps</b>");
		gtk_widget_show(frameResizeFixStep);
		gtk_box_pack_start(GTK_BOX(vboxResize), frameResizeFixStep, TRUE, TRUE, 0);
		//Add alingment for frame
		GtkWidget* alingmentFrameResizeFixStep = gtk_alignment_new(
					  			  0.5,
					  			  0.5,
					  			  1,
					  			  1);
		gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameResizeFixStep),0,0,6,3);
		gtk_widget_show(alingmentFrameResizeFixStep);
		gtk_container_add(GTK_CONTAINER(frameResizeFixStep), alingmentFrameResizeFixStep);
			//Add table for frame:
	  	  GtkWidget* tblResizeFixStep = gtk_table_new(2,3,FALSE);
	  	  gtk_table_set_col_spacings(GTK_TABLE(tblResizeFixStep), 3);
	  	  gtk_widget_show(tblResizeFixStep);
	  	  gtk_container_add(GTK_CONTAINER(alingmentFrameResizeFixStep), tblResizeFixStep);
	  	  adjStepWidth = gimp_scale_entry_new(
	  				   						  GTK_TABLE(tblResizeFixStep), //table
	  				   						  0,			//column
	  				   						  0,			//row
	  				   						  "Step Width:",		//text
	  				   						  50,			//minimum horizontal size of the GtkHScale.
	  				   						  60,			//minimum horizontal size of the GtkSpinButton.
	  				   						  pl_vals.step_width,//The initial value
	  				   						  -layerData.w,			//The lower boundary
	  				   						  2000,			//The upper boundary
	  				   						  1,			//The step increment
	  				   						  1,			//The page increment (??)
	  				   						  0,			//number of decimal digits
	  				   						  TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
	  				   						  0,			//spinbutton's lower boundary if constrain == FALSE
	  				   						  0,			//spinbutton's upper boundary if constrain == FALSE
	  				   						  "",	//A tooltip message for the scale and the spinbutton
	  				   						  NULL //The widgets' help_id
	  				   				  );
	  	  	g_signal_connect(adjStepWidth, "value_changed",
	  				   		G_CALLBACK (gimp_int_adjustment_update),
	  				   		&pl_vals.step_width);

	  	   g_signal_connect(adjStepWidth, "value_changed",
	  	  			  		G_CALLBACK (on_size_changed),
	  	  			  		GINT_TO_POINTER(CHK_SET_W));
	  	 g_signal_connect(adjStepWidth, "value_changed",
	  	 				  	  		G_CALLBACK (checkValues),
	  	 				  	  		 GINT_TO_POINTER(CHK_SET_W));

		  	adjStepHeight = gimp_scale_entry_new(
		  				   					GTK_TABLE(tblResizeFixStep), //table
		  				   					0,			//column
		  				   					1,			//row
		  				   					"Step Height:",		//text
		  				   					50,			//minimum horizontal size of the GtkHScale.
		  				   					60,			//minimum horizontal size of the GtkSpinButton.
		  				   					pl_vals.step_height,//The initial value
		  				   					-layerData.h,		//The lower boundary
		  				   					2000,		//The upper boundary
		  				   					1,			//The step increment
		  				   					1,			//The page increment (??)
		  				   					0,			//number of decimal digits
		  				   					TRUE,		//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
		  				   					0,			//spinbutton's lower boundary if constrain == FALSE
		  				   					0,			//spinbutton's upper boundary if constrain == FALSE
		  				   					"",			//A tooltip message for the scale and the spinbutton
		  				   					NULL 		//The widgets' help_id
		  				   				  );
		  	  	g_signal_connect(adjStepHeight, "value_changed",
		  				   		G_CALLBACK (gimp_int_adjustment_update),
		  				   		&pl_vals.step_height);
		  	  	g_signal_connect(adjStepHeight, "value_changed",
		  	  				  	G_CALLBACK (on_size_changed),
		  	  				GINT_TO_POINTER(CHK_SET_H));
		  	  g_signal_connect(adjStepHeight, "value_changed",
		  	  		G_CALLBACK (checkValues),
		  	  		 GINT_TO_POINTER(CHK_SET_H));

			  	//Add frame for Random steps
			  	GtkWidget* frameResizeRanStep = gtk_frame_new("");
			  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameResizeRanStep))),"<b>Random Steps</b>");
			  	gtk_widget_show(frameResizeRanStep);
			  	gtk_box_pack_start(GTK_BOX(vboxResize), frameResizeRanStep, TRUE, TRUE, 0);
			  	//Add alingment for frame
			  	GtkWidget* alingmentFrameResizeRanStep = gtk_alignment_new(
			  			  0.5,
			  			  0.5,
			  			  1,
			  			  1);
			  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameResizeRanStep),0,0,6,3);
			  	gtk_widget_show(alingmentFrameResizeRanStep);
			  	gtk_container_add(GTK_CONTAINER(frameResizeRanStep), alingmentFrameResizeRanStep);
				  //Add table for frame:
			  	  GtkWidget* tblResizeRanStep = gtk_table_new(2,4,FALSE);
			  	  gtk_table_set_col_spacings(GTK_TABLE(tblResizeRanStep), 3);
			  	  gtk_widget_show(tblResizeRanStep);
			  	  gtk_container_add(GTK_CONTAINER(alingmentFrameResizeRanStep), tblResizeRanStep);
			  	  GtkWidget* lbRanStepWidthMin = gtk_label_new("Step Width min.:");
			  	  spbRanStepWidthMin = gimp_spin_button_new(
			  			  &adjRanStepWidthMin,
			  			  pl_vals.ran_step_width_min,
			  			  -layerData.w, 2000,
			  			  1, 1,
			  			  1,
			  			  10,
			  			  0);
			  	  GtkWidget* lbRanStepWidthMax = gtk_label_new("Width max.:");
			  	  spbRanStepWidthMax= gimp_spin_button_new(
			  			  &adjRanStepWidthMax,
			  			  pl_vals.ran_step_width_max,
			  			-layerData.w, 2000,
			  			  1, 1,
			  			  1,
			  			  10,
			  			  0);
			  	  GtkWidget* lbRanStepHeightMin = gtk_label_new("Step Height min.:");
			  	  spbRanStepHeightMin = gimp_spin_button_new(
			  			  &adjRanStepHeightMin,
			  			  pl_vals.ran_step_height_min,
			  			-layerData.h, 2000,
			  			  1, 1,
			  			  1,
			  			  10,
			  			  0);
			  	  GtkWidget* lbRanStepHeightMax = gtk_label_new("Height max.:");
			  	  spbRanStepHeightMax= gimp_spin_button_new(
			  			  &adjRanStepHeightMax,
			  			  pl_vals.ran_step_height_max,
			  			-layerData.h, 2000,
			  			  1, 1,
			  			  1,
			  			  10,
			  			  0);
				  	gtk_widget_show(spbRanStepWidthMin);
				  	gtk_widget_show(spbRanStepWidthMax);
				  	gtk_widget_show(spbRanStepHeightMin);
				  	gtk_widget_show(spbRanStepHeightMax);
				  	gtk_widget_show(lbRanStepWidthMin); gtk_widget_show(lbRanStepWidthMax);
				  	gtk_widget_show(lbRanStepHeightMin); gtk_widget_show(lbRanStepHeightMax);

				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), lbRanStepWidthMin,0,1,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), spbRanStepWidthMin,1,2,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), lbRanStepWidthMax,2,3,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), spbRanStepWidthMax,3,4,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), lbRanStepHeightMin,0,1,1,2);
				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), spbRanStepHeightMin,1,2,1,2);
				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), lbRanStepHeightMax,2,3,1,2);
				  	gtk_table_attach_defaults(GTK_TABLE(tblResizeRanStep), spbRanStepHeightMax,3,4,1,2);

				  	g_signal_connect(adjRanStepWidthMin, "value_changed",
				  	                      G_CALLBACK (gimp_int_adjustment_update),
				  	                      &pl_vals.ran_step_width_min);
				  	g_signal_connect(adjRanStepWidthMax, "value_changed",
				  	                      G_CALLBACK (gimp_int_adjustment_update),
				  	                      &pl_vals.ran_step_width_max);
				  	g_signal_connect(adjRanStepHeightMin, "value_changed",
				  	                      G_CALLBACK (gimp_int_adjustment_update),
				  	                      &pl_vals.ran_step_height_min);
				  	g_signal_connect(adjRanStepHeightMax, "value_changed",
				  	                      G_CALLBACK (gimp_int_adjustment_update),
				  	                      &pl_vals.ran_step_height_max);

				  	g_signal_connect(adjRanStepWidthMin, "value_changed",
				  			G_CALLBACK(checkValues),
				  			GINT_TO_POINTER(CHK_MIN_STEP_W));
				  	g_signal_connect(adjRanStepWidthMax, "value_changed",
				  			G_CALLBACK(checkValues),
				  			GINT_TO_POINTER(CHK_MAX_STEP_W));
				  	g_signal_connect(adjRanStepHeightMin, "value_changed",
				  			G_CALLBACK(checkValues),
				  			GINT_TO_POINTER(CHK_MIN_STEP_H));
				  	g_signal_connect(adjRanStepHeightMax, "value_changed",
				  			G_CALLBACK(checkValues),
				  			GINT_TO_POINTER(CHK_MAX_STEP_H));

		//Add frame for Keep Ratio
			GtkWidget* frameAspectRatio = gtk_frame_new("");
			gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameAspectRatio))),"<b>Aspect Ratio</b>");
			gtk_widget_show(frameAspectRatio);
			gtk_box_pack_start(GTK_BOX(vboxResize), frameAspectRatio, TRUE, TRUE, 0);
			//Add alingment for frame
			GtkWidget* alingmentFrameAspectRatio = gtk_alignment_new(
									  			  0.5,
									  			  0.5,
									  			  1,
									  			  1);
			gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameAspectRatio),0,0,6,3);
			gtk_widget_show(alingmentFrameAspectRatio);
			gtk_container_add(GTK_CONTAINER(frameAspectRatio), alingmentFrameAspectRatio);
			GtkWidget* hboxAspectRatio = gtk_hbox_new(FALSE, 6);
			gtk_widget_show(hboxAspectRatio);
			gtk_container_add(GTK_CONTAINER(alingmentFrameAspectRatio), hboxAspectRatio);
			chkAspectRatio = gtk_check_button_new_with_label("Keep aspect:");
			gtk_widget_show(chkAspectRatio);
			gtk_box_pack_start(GTK_BOX(hboxAspectRatio), chkAspectRatio, FALSE, TRUE, 0);

			g_signal_connect(chkAspectRatio, "toggled",
									  			G_CALLBACK(on_set_aspect_ratio),
									  			NULL);

		//Add frame for Direction Resize Types
			GtkWidget* frameResizeType = gtk_frame_new("");
			gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameResizeType))),"<b>Resize Type</b>");
			gtk_widget_show(frameResizeType);
			gtk_box_pack_start(GTK_BOX(vboxResize), frameResizeType, TRUE, TRUE, 0);
			//Add alingment for frame
			GtkWidget* alingmentFrameResizeType = gtk_alignment_new(
				  			  0.5,
				  			  0.5,
				  			  1,
				  			  1);
			gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameResizeType),0,0,6,3);
			gtk_widget_show(alingmentFrameResizeType);
			gtk_container_add(GTK_CONTAINER(frameResizeType), alingmentFrameResizeType);
				//Add table for frame:
		  	  GtkWidget* tblFrameResizeType = gtk_table_new(1,2,FALSE);
		  	  gtk_widget_show(tblFrameResizeType);
		  	  gtk_container_add(GTK_CONTAINER(alingmentFrameResizeType), tblFrameResizeType);
				  	  //Add elements
					  lbResizeType = gtk_label_new("Type of Direction Resize");
				  	  gtk_widget_show(lbResizeType);
				  	  gtk_table_attach_defaults(GTK_TABLE(tblFrameResizeType), lbResizeType,0,1,0,1);

				  	GtkWidget* tblAutoResizeType = gtk_table_new(3,3,FALSE);
				  	gtk_widget_show(tblAutoResizeType);
				  	gtk_table_attach(
						  GTK_TABLE(tblFrameResizeType),
						  tblAutoResizeType,
						  1,2,
						  0,1,
						  GTK_EXPAND,
						  GTK_EXPAND,
						  3,3
						  );

				  	GSList *listAutoResizeType=NULL;
				  	rbResizeTopLeft = gtk_radio_button_new(NULL);
				  	listAutoResizeType = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbResizeTopLeft));
				  	rbResizeTopRight = gtk_radio_button_new(listAutoResizeType);
				  	listAutoResizeType = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbResizeTopRight));
				  	rbResizeCenter = gtk_radio_button_new(listAutoResizeType);
				  	listAutoResizeType = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbResizeCenter));
				  	rbResizeBottomLeft = gtk_radio_button_new(listAutoResizeType);
				  	listAutoResizeType = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbResizeBottomLeft));
				  	rbResizeBottomRight  = gtk_radio_button_new(listAutoResizeType);
				  	listAutoResizeType = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbResizeBottomRight));
				  	gtk_widget_show(rbResizeTopLeft);
				  	gtk_widget_show(rbResizeTopRight);
				  	gtk_widget_show(rbResizeCenter);
				  	gtk_widget_show(rbResizeBottomLeft);
				  	gtk_widget_show(rbResizeBottomRight);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoResizeType), rbResizeTopLeft,0,1,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoResizeType), rbResizeTopRight,2,3,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoResizeType), rbResizeCenter,1,2,1,2);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoResizeType), rbResizeBottomLeft,0,1,2,3);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoResizeType), rbResizeBottomRight,2,3,2,3);

				  	g_signal_connect(rbResizeTopLeft, "toggled",
				  					  G_CALLBACK (on_set_resize_type_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_LEFT));
				  	g_signal_connect(rbResizeTopRight, "toggled",
				  					  G_CALLBACK (on_set_resize_type_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_RIGHT));
				  	g_signal_connect(rbResizeCenter, "toggled",
				  					  G_CALLBACK (on_set_resize_type_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)CENTER_CENTER));
				  	g_signal_connect(rbResizeBottomLeft, "toggled",
				  					  G_CALLBACK (on_set_resize_type_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_LEFT));
				  	g_signal_connect(rbResizeBottomRight, "toggled",
				  					  G_CALLBACK (on_set_resize_type_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_RIGHT));


	  	 ////////////////////////////////////
		//Add Rotation expander panels:
	    ///////////////////////////////////////////////////
	  	  GtkWidget* epRotation = gtk_expander_new(
	  			  "<span foreground='#00438A'><b>ROTATE</b></span>"
	  			  );
	  	gtk_expander_set_use_markup(GTK_EXPANDER(epRotation), TRUE);
		  gtk_widget_show(epRotation);
		  gtk_box_pack_start(GTK_BOX(vboxExpander), epRotation, FALSE, TRUE, 0);
		  	  //Add alignment
		  	  GtkWidget* alignmentRotate = gtk_alignment_new(
		  			  0.5,
		  			  0.5,
		  			  1,
		  			  1);
		  	gtk_alignment_set_padding(GTK_ALIGNMENT(alignmentRotate),0,0,6,6);
		  	gtk_widget_show(alignmentRotate);
		  	gtk_container_add(GTK_CONTAINER(epRotation), alignmentRotate);
		  	//Add vbox for frames
		  	GtkWidget* vboxRorate =  gtk_vbox_new (FALSE, 0);
		  	gtk_widget_show(vboxRorate);
		  	gtk_container_add(GTK_CONTAINER(alignmentRotate), vboxRorate);
		  	//Add frame for manual angle
		  	GtkWidget* frameManAngle = gtk_frame_new("");
		  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameManAngle))),"<b>Fixed Angle:</b>");
		  	gtk_widget_show(frameManAngle);
		  	gtk_box_pack_start(GTK_BOX(vboxRorate), frameManAngle, TRUE, TRUE, 0);
		  	//Add alingment for frame
		  	GtkWidget* alingmentFrameManAngel = gtk_alignment_new(
		  			  0.5,
		  			  0.5,
		  			  1,
		  			  1);
		  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameManAngel),0,0,6,3);
		  	gtk_widget_show(alingmentFrameManAngel);
		  	gtk_container_add(GTK_CONTAINER(frameManAngle), alingmentFrameManAngel);
			  //Add table for frame:
		  	  GtkWidget* tblRotate = gtk_table_new(1,1,FALSE);
		  	  gtk_table_set_col_spacings(GTK_TABLE(tblRotate), 3);
		  	  gtk_widget_show(tblRotate);
		  	  gtk_container_add(GTK_CONTAINER(alingmentFrameManAngel), tblRotate);
		  	  adjAngle = gimp_scale_entry_new(
		  				   						  GTK_TABLE(tblRotate), //table
		  				   						  0,			//column
		  				   						  0,			//row
		  				   						  "Angle:",		//text
		  				   						  120,			//minimum horizontal size of the GtkHScale.
		  				   						  60,			//minimum horizontal size of the GtkSpinButton.
		  				   						  pl_vals.angle,//The initial value
		  				   						  -360,			//The lower boundary
		  				   						  360,			//The upper boundary
		  				   						  1,			//The step increment
		  				   						  1,			//The page increment (??)
		  				   						  0,			//number of decimal digits
		  				   						  TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
		  				   						  0,			//spinbutton's lower boundary if constrain == FALSE
		  				   						  0,			//spinbutton's upper boundary if constrain == FALSE
		  				   						  "Rotate at that angles by each clone times.",	//A tooltip message for the scale and the spinbutton
		  				   						  NULL //The widgets' help_id
		  				   				  );
		  	 g_signal_connect(adjAngle, "value_changed",
		  				   		G_CALLBACK (gimp_int_adjustment_update),
		  				   			&pl_vals.angle);

		  	  g_signal_connect(adjAngle, "value_changed",
		  	  		  				   		G_CALLBACK (checkValues),
		  	  		  				  GINT_TO_POINTER(CHK_ANGLE));

		  	//Add frame for random angle
		  	GtkWidget* frameRandomAngle = gtk_frame_new("");
		  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameRandomAngle))),"<b>Random Angle:</b>");
		  	gtk_widget_show(frameRandomAngle);
		  	gtk_box_pack_start(GTK_BOX(vboxRorate), frameRandomAngle, TRUE, TRUE, 0);
		  	//Add alingment for frame
		  	GtkWidget* alingmentFrameRandomAngel = gtk_alignment_new(
		  			  			  0.5,
		  			  			  0.5,
		  			  			  1,
		  			  			  1);
		  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameRandomAngel),0,0,6,3);
		  	gtk_widget_show(alingmentFrameRandomAngel);
		  	gtk_container_add(GTK_CONTAINER(frameRandomAngle), alingmentFrameRandomAngel);
		  		//Add table for frame:
		  		GtkWidget *tblRandomAngle = gtk_table_new(1,2,FALSE);
		  		gtk_table_set_col_spacings(GTK_TABLE(tblRandomAngle), 3);
		  		gtk_widget_show(tblRandomAngle);
		  		gtk_container_add(GTK_CONTAINER(alingmentFrameRandomAngel), tblRandomAngle);
		  		adjRandomAngleFrom = gimp_scale_entry_new(
		  				  	GTK_TABLE(tblRandomAngle), //table
		  				  	0,			//column
		  				  	0,			//row
		  				  	"Angle Min:",		//text
		  				  	60,		//minimum horizontal size of the GtkHScale.
		  				  	60,			//minimum horizontal size of the GtkSpinButton.
		  				  	pl_vals.random_angle_from,			//The initial value
		  				  	-360,		//The lower boundary
		  				  	360,		//The upper boundary
		  				  	1,			//The step increment
		  				  	1,			//The page increment (??)
		  				  	0,			//number of decimal digits
		  				  	TRUE,		//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
		  				  	0,			//spinbutton's lower boundary if constrain == FALSE
		  				  	0,			//spinbutton's upper boundary if constrain == FALSE
		  				  	"",	//A tooltip message for the scale and the spinbutton
		  				  	NULL //The widgets' help_id
		  				  	);
		  		adjRandomAngleTo = gimp_scale_entry_new(
		  				  	GTK_TABLE(tblRandomAngle), //table
		  				  	0,			//column
		  				  	1,			//row
		  				  	"Angle Max:",		//text
		  				  	60,		//minimum horizontal size of the GtkHScale.
		  				  	60,			//minimum horizontal size of the GtkSpinButton.
		  				  	pl_vals.random_angle_to,			//The initial value
		  				  	-360,		//The lower boundary
		  				  	360,		//The upper boundary
		  				  	1,			//The step increment
		  				  	1,			//The page increment (??)
		  				  	0,			//number of decimal digits
		  				  	TRUE,		//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
		  				  	0,			//spinbutton's lower boundary if constrain == FALSE
		  				  	0,			//spinbutton's upper boundary if constrain == FALSE
		  				  	"",	//A tooltip message for the scale and the spinbutton
		  				  	NULL //The widgets' help_id
		  				  				  	);
		  		g_signal_connect(adjRandomAngleFrom, "value_changed",
		  				  				   		G_CALLBACK (gimp_int_adjustment_update),
		  				  				   			&pl_vals.random_angle_from);

		  		g_signal_connect(adjRandomAngleTo, "value_changed",
		  				  				   		G_CALLBACK (gimp_int_adjustment_update),
		  				  				   			&pl_vals.random_angle_to);

		  		g_signal_connect(adjRandomAngleFrom, "value_changed",
		  				G_CALLBACK(checkValues), GINT_TO_POINTER(CHK_MIN_ANGLE));

		  		g_signal_connect(adjRandomAngleTo, "value_changed",
		  				  				  G_CALLBACK (checkValues),
		  				  				GINT_TO_POINTER(CHK_MAX_ANGLE));

		  		//Add frame for random angle
		  		GtkWidget* frameRotateCoords = gtk_frame_new("");
		  		gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameRotateCoords))),"<b>Rotation Coordinates:</b>");
		  		gtk_widget_show(frameRotateCoords);
		  		gtk_box_pack_start(GTK_BOX(vboxRorate), frameRotateCoords, TRUE, TRUE, 0);
			  	//Add alingment for frame
			  	GtkWidget* alingmentFrameRotateCoords = gtk_alignment_new(
			  			  0.5,
			  			  0.5,
			  			  1,
			  			  1);
			  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameRotateCoords),0,0,6,3);
			  	gtk_widget_show(alingmentFrameRotateCoords);
			  	gtk_container_add(GTK_CONTAINER(frameRotateCoords), alingmentFrameRotateCoords);
				  //Add table for frame:
			  	  GtkWidget* tblFrameRotateCoords = gtk_table_new(3,2,FALSE);
				  gtk_widget_show(tblFrameRotateCoords);
				  gtk_container_add(GTK_CONTAINER(alingmentFrameRotateCoords), tblFrameRotateCoords);
				  	  //Add elements
					  GtkWidget* lbManRotateCoords = gtk_label_new("");
					  GtkWidget* lbAutoRotateCoords = gtk_label_new("Get Coordinates:");
					  gtk_widget_show(lbManRotateCoords);
					  gtk_widget_show(lbAutoRotateCoords);
					  gtk_table_attach_defaults(GTK_TABLE(tblFrameRotateCoords), lbManRotateCoords,0,1,0,1);
					  gtk_table_attach_defaults(GTK_TABLE(tblFrameRotateCoords), lbAutoRotateCoords,1,2,0,1);
					  GtkWidget* tblManRotateCoords = gtk_table_new(2,2,FALSE);
					  gtk_widget_show(tblManRotateCoords);
					  gtk_table_attach_defaults(GTK_TABLE(tblFrameRotateCoords), tblManRotateCoords,0,1,1,2);
					  GtkWidget* lbManRotateCoordX = gtk_label_new("Center X:");
					  GtkWidget* lbManRotateCoordY = gtk_label_new("Center Y:");
				  	  gtk_widget_show(lbManRotateCoordX);
				  	  gtk_widget_show(lbManRotateCoordY);
				  	  gtk_table_attach_defaults(GTK_TABLE(tblManRotateCoords), lbManRotateCoordX,0,1,0,1);
				  	  gtk_table_attach_defaults(GTK_TABLE(tblManRotateCoords), lbManRotateCoordY,0,1,1,2);
				  	  spbManRotateCoordX = gimp_spin_button_new(
				  			  &adjManRotateCoordX,
				  			  pl_vals.pX,
				  			  0, 10000,
				  			  1, 1,
				  			  1,
				  			  10,
				  			  0);
				  	 spbManRotateCoordY = gimp_spin_button_new(
				  			  &adjManRotateCoordY,
				  			  pl_vals.pY,
				  			  0, 10000,
				  			  1, 1,
				  			  1,
				  			  10,
				  			  0);
				  	gtk_widget_show(spbManRotateCoordX);
				  	gtk_widget_show(spbManRotateCoordY);
				  	gtk_table_attach_defaults(GTK_TABLE(tblManRotateCoords), spbManRotateCoordX,1,2,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblManRotateCoords), spbManRotateCoordY,1,2,1,2);
				  	g_signal_connect(adjManRotateCoordX, "value_changed",
				  	                      G_CALLBACK (gimp_int_adjustment_update),
				  	                      &pl_vals.pX);

				  	g_signal_connect(adjManRotateCoordY, "value_changed",
				  	                      G_CALLBACK (gimp_int_adjustment_update),
				  	                      &pl_vals.pY);

				  	GtkWidget* tblAutoRotateCoord = gtk_table_new(3,3,FALSE);
				  	gtk_widget_show(tblAutoRotateCoord);
				  	gtk_table_attach(
						  GTK_TABLE(tblFrameRotateCoords),
						  tblAutoRotateCoord,
						  1,2,
						  1,2,
						  GTK_EXPAND,
						  GTK_EXPAND,
						  3,3
						  );

				  	GSList *listAutoRotateCoords=NULL;
				  	rbRotateTopLeft = gtk_radio_button_new(NULL);
				  	listAutoRotateCoords = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbRotateTopLeft));
				  	rbRotateTopRight = gtk_radio_button_new(listAutoRotateCoords);
				  	listAutoRotateCoords = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbRotateTopRight));
				  	rbRotateCenter = gtk_radio_button_new(listAutoRotateCoords);
				  	listAutoRotateCoords = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbRotateCenter));
				  	rbRotateBottomLeft = gtk_radio_button_new(listAutoRotateCoords);
				  	listAutoRotateCoords = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbRotateBottomLeft));
				  	rbRotateBottomRight  = gtk_radio_button_new(listAutoRotateCoords);
				  	listAutoRotateCoords = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbRotateBottomRight));
				  	gtk_widget_show(rbRotateTopLeft);
				  	gtk_widget_show(rbRotateTopRight);
				  	gtk_widget_show(rbRotateCenter);
				  	gtk_widget_show(rbRotateBottomLeft);
				  	gtk_widget_show(rbRotateBottomRight);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoRotateCoord), rbRotateTopLeft,0,1,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoRotateCoord), rbRotateTopRight,2,3,0,1);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoRotateCoord), rbRotateCenter,1,2,1,2);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoRotateCoord), rbRotateBottomLeft,0,1,2,3);
				  	gtk_table_attach_defaults(GTK_TABLE(tblAutoRotateCoord), rbRotateBottomRight,2,3,2,3);

				  	g_signal_connect(rbRotateTopLeft, "toggled",
				  					  G_CALLBACK (on_set_auto_coord_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_LEFT));
				  	g_signal_connect(rbRotateTopRight, "toggled",
				  					  G_CALLBACK (on_set_auto_coord_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_RIGHT));
				  	g_signal_connect(rbRotateCenter, "toggled",
				  					  G_CALLBACK (on_set_auto_coord_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)CENTER_CENTER));
				  	g_signal_connect(rbRotateBottomLeft, "toggled",
				  					  G_CALLBACK (on_set_auto_coord_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_LEFT));
				  	g_signal_connect(rbRotateBottomRight, "toggled",
				  					  G_CALLBACK (on_set_auto_coord_radio),
				  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_RIGHT));


				  	GSList *listRotateSource=NULL;
				  	rbRotateFixed = gtk_radio_button_new_with_label (NULL,
				  			"permanent coordinates");
				  	listRotateSource = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbRotateFixed));
				  	rbRotateDinamically = gtk_radio_button_new_with_label (listRotateSource,
				  			"dynamic coordinates");
				  	listRotateSource = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbRotateDinamically));
				  	gtk_widget_show(rbRotateFixed);
				  	gtk_widget_show(rbRotateDinamically);

				  	gtk_table_attach_defaults(GTK_TABLE(tblFrameRotateCoords), rbRotateFixed,0,1,2,3);
				  	gtk_table_attach_defaults(GTK_TABLE(tblFrameRotateCoords), rbRotateDinamically,1,2,2,3);

				  	g_signal_connect(rbRotateFixed, "toggled",
				  			G_CALLBACK (on_set_rotate_coord_radio),
				  			GINT_TO_POINTER((enum TYPE_ROTATE_COORDINATES)FIXED));
				  	g_signal_connect(rbRotateDinamically, "toggled",
				  			G_CALLBACK (on_set_rotate_coord_radio),
				  			GINT_TO_POINTER((enum TYPE_ROTATE_COORDINATES)DINAMIC));

		  //////////////////////////////////////////////////////////
		  //Add Move expander panels:
		  //////////////////////////////////////////////////////////
			GtkWidget* epMove = gtk_expander_new(
					"<span foreground='#00438A'><b>MOVE</b></span>"
					);
			gtk_expander_set_use_markup(GTK_EXPANDER(epMove), TRUE);
			gtk_widget_show(epMove);
			gtk_box_pack_start(GTK_BOX(vboxExpander), epMove, FALSE, TRUE, 0);
			//Add alignment
			  	  GtkWidget* alignmentMove = gtk_alignment_new(
			  			  0.5,
			  			  0.5,
			  			  1,
			  			  1);
			  	gtk_alignment_set_padding(GTK_ALIGNMENT(alignmentMove),0,0,6,6);
			  	gtk_widget_show(alignmentMove);
			  	gtk_container_add(GTK_CONTAINER(epMove), alignmentMove);
			  	//Add vbox for frames
			  	GtkWidget* vboxMove =  gtk_vbox_new (FALSE, 0);
			  	gtk_widget_show(vboxMove);
			  	gtk_container_add(GTK_CONTAINER(alignmentMove), vboxMove);
			  	//Add frame for Fixed steps
			  	GtkWidget* frameMoveFixStep = gtk_frame_new("");
			  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameMoveFixStep))),"<b>Fixed Steps</b>");
			  	gtk_widget_show(frameMoveFixStep);
			  	gtk_box_pack_start(GTK_BOX(vboxMove), frameMoveFixStep, TRUE, TRUE, 0);
			  	//Add alingment for frame
			  	GtkWidget* alingmentFrameFixStep = gtk_alignment_new(
			  			  0.5,
			  			  0.5,
			  			  1,
			  			  1);
			  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameFixStep),0,0,6,3);
			  	gtk_widget_show(alingmentFrameFixStep);
			  	gtk_container_add(GTK_CONTAINER(frameMoveFixStep), alingmentFrameFixStep);
				  //Add table for frame:
			  	  GtkWidget* tblMoveFixStep = gtk_table_new(2,3,FALSE);
			  	  gtk_table_set_col_spacings(GTK_TABLE(tblMoveFixStep), 3);
			  	  gtk_widget_show(tblMoveFixStep);
			  	  gtk_container_add(GTK_CONTAINER(alingmentFrameFixStep), tblMoveFixStep);
			  	  adjStepX = gimp_scale_entry_new(
			  				   						  GTK_TABLE(tblMoveFixStep), //table
			  				   						  0,			//column
			  				   						  0,			//row
			  				   						  "Step X:",		//text
			  				   						  60,			//minimum horizontal size of the GtkHScale.
			  				   						  70,			//minimum horizontal size of the GtkSpinButton.
			  				   						  pl_vals.step_x,//The initial value
			  				   						  -1000,			//The lower boundary
			  				   						  1000,			//The upper boundary
			  				   						  1,			//The step increment
			  				   						  1,			//The page increment (??)
			  				   						  0,			//number of decimal digits
			  				   						  TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
			  				   						  0,			//spinbutton's lower boundary if constrain == FALSE
			  				   						  0,			//spinbutton's upper boundary if constrain == FALSE
			  				   						  "",	//A tooltip message for the scale and the spinbutton
			  				   						  NULL //The widgets' help_id
			  				   				  );
			  	  	g_signal_connect(adjStepX, "value_changed",
			  				   		G_CALLBACK (gimp_int_adjustment_update),
			  				   			&pl_vals.step_x);
			  	  g_signal_connect(adjStepX, "value_changed",
			  	  		G_CALLBACK (checkValues),
			  	  		 GINT_TO_POINTER(CHK_STEP_X));

				  	adjStepY = gimp_scale_entry_new(
				  				   					GTK_TABLE(tblMoveFixStep), //table
				  				   					0,			//column
				  				   					1,			//row
				  				   					"Step Y:",		//text
				  				   					60,			//minimum horizontal size of the GtkHScale.
				  				   					70,			//minimum horizontal size of the GtkSpinButton.
				  				   					pl_vals.step_y,//The initial value
				  				   					-1000,		//The lower boundary
				  				   					1000,		//The upper boundary
				  				   					1,			//The step increment
				  				   					1,			//The page increment (??)
				  				   					0,			//number of decimal digits
				  				   					TRUE,		//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
				  				   					0,			//spinbutton's lower boundary if constrain == FALSE
				  				   					0,			//spinbutton's upper boundary if constrain == FALSE
				  				   					"",			//A tooltip message for the scale and the spinbutton
				  				   					NULL 		//The widgets' help_id
				  				   				  );
				  	  	g_signal_connect(adjStepY, "value_changed",
				  				   			G_CALLBACK (gimp_int_adjustment_update),
				  				   				&pl_vals.step_y);
				  	  g_signal_connect(adjStepY, "value_changed",
				  	  			  	  		G_CALLBACK (checkValues),
				  	  			  	  		 GINT_TO_POINTER(CHK_STEP_Y));
					  	//Add frame for Random steps
					  	GtkWidget* frameMoveRanStep = gtk_frame_new("");
					  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameMoveRanStep))),"<b>Random Steps</b>");
					  	gtk_widget_show(frameMoveRanStep);
					  	gtk_box_pack_start(GTK_BOX(vboxMove), frameMoveRanStep, TRUE, TRUE, 0);
					  	//Add alingment for frame
					  	GtkWidget* alingmentFrameRanStep = gtk_alignment_new(
					  			  0.5,
					  			  0.5,
					  			  1,
					  			  1);
					  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameRanStep),0,0,6,3);
					  	gtk_widget_show(alingmentFrameRanStep);
					  	gtk_container_add(GTK_CONTAINER(frameMoveRanStep), alingmentFrameRanStep);
						  //Add table for frame:
					  	  GtkWidget* tblMoveRanStep = gtk_table_new(2,4,FALSE);
					  	  gtk_table_set_col_spacings(GTK_TABLE(tblMoveRanStep), 3);
					  	  gtk_widget_show(tblMoveRanStep);
					  	  gtk_container_add(GTK_CONTAINER(alingmentFrameRanStep), tblMoveRanStep);
					  	  GtkWidget* lbRanStepXMin = gtk_label_new("Step X min. :");
					  	  spbRanStepXMin = gimp_spin_button_new(
					  			  &adjRanStepXMin,
					  			  pl_vals.ran_step_x_min,
					  			  -1000, 1000,
					  			  1, 1,
					  			  1,
					  			  10,
					  			  0);
					  	  GtkWidget* lbRanStepXMax = gtk_label_new(" X max. :");
					  	  spbRanStepXMax= gimp_spin_button_new(
					  			  &adjRanStepXMax,
					  			  pl_vals.ran_step_x_max,
					  			  -1000, 1000,
					  			  1, 1,
					  			  1,
					  			  10,
					  			  0);
					  	  GtkWidget* lbRanStepYMin = gtk_label_new("Step Y min. :");
					  	  spbRanStepYMin = gimp_spin_button_new(
					  			  &adjRanStepYMin,
					  			  pl_vals.ran_step_y_min,
					  			  -1000, 1000,
					  			  1, 1,
					  			  1,
					  			  10,
					  			  0);
					  	  GtkWidget* lbRanStepyMax = gtk_label_new(" Y max. :");
					  	  spbRanStepYMax= gimp_spin_button_new(
					  			  &adjRanStepYMax,
					  			  pl_vals.ran_step_y_max,
					  			  -1000, 1000,
					  			  1, 1,
					  			  1,
					  			  10,
					  			  0);
						  	gtk_widget_show(spbRanStepXMin);
						  	gtk_widget_show(spbRanStepXMax);
						  	gtk_widget_show(spbRanStepYMin);
						  	gtk_widget_show(spbRanStepYMax);
						  	gtk_widget_show(lbRanStepXMin); gtk_widget_show(lbRanStepXMax);
						  	gtk_widget_show(lbRanStepYMin); gtk_widget_show(lbRanStepyMax);

						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), lbRanStepXMin,0,1,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), spbRanStepXMin,1,2,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), lbRanStepXMax,2,3,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), spbRanStepXMax,3,4,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), lbRanStepYMin,0,1,1,2);
						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), spbRanStepYMin,1,2,1,2);
						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), lbRanStepyMax,2,3,1,2);
						  	gtk_table_attach_defaults(GTK_TABLE(tblMoveRanStep), spbRanStepYMax,3,4,1,2);

						  	g_signal_connect(adjRanStepXMin, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.ran_step_x_min);
						  	g_signal_connect(adjRanStepXMax, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.ran_step_x_max);
						  	g_signal_connect(adjRanStepYMin, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.ran_step_y_min);
						  	g_signal_connect(adjRanStepYMax, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.ran_step_y_max);

						  	g_signal_connect(adjRanStepXMin, "value_changed",
						  			  				G_CALLBACK(checkValues),
						  			  				GINT_TO_POINTER(CHK_MIN_STEP_X));
						  	g_signal_connect(adjRanStepXMax, "value_changed",
						  							G_CALLBACK(checkValues),
						  							GINT_TO_POINTER(CHK_MAX_STEP_X));
						  	g_signal_connect(adjRanStepYMin, "value_changed",
						  			  				G_CALLBACK(checkValues),
						  			  				GINT_TO_POINTER(CHK_MIN_STEP_Y));
						  	g_signal_connect(adjRanStepYMax, "value_changed",
						  							G_CALLBACK(checkValues),
						  							GINT_TO_POINTER(CHK_MAX_STEP_Y));

						  	//Add frame for start-corner step
						  	GtkWidget* frameMoveStartCorner = gtk_frame_new("");
						  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameMoveStartCorner))),"<b>Move Layer From:</b>");
						  	gtk_widget_show(frameMoveStartCorner);
						  	gtk_box_pack_start(GTK_BOX(vboxMove), frameMoveStartCorner, TRUE, TRUE, 0);
						  	//Add alingment for frame
						  	GtkWidget* alingmentFrameStartCorner = gtk_alignment_new(
						  			  0.5,
						  			  0.5,
						  			  1,
						  			  1);
						  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameStartCorner),0,0,6,3);
						  	gtk_widget_show(alingmentFrameStartCorner);
						  	gtk_container_add(GTK_CONTAINER(frameMoveStartCorner), alingmentFrameStartCorner);
						  	GtkWidget* hboxCorner = gtk_hbox_new(FALSE,3);
						  	gtk_widget_show(hboxCorner);
						  	gtk_container_add(GTK_CONTAINER(alingmentFrameStartCorner), hboxCorner);

						  	GtkWidget* vboxCornerLabels = gtk_vbox_new(FALSE,0);
						  	gtk_widget_show(vboxCornerLabels);
						  	gtk_box_pack_start(GTK_BOX(hboxCorner), vboxCornerLabels,TRUE,TRUE,0);
						  	GtkWidget* vrCorner1 = gtk_vseparator_new();
						  	gtk_widget_show(vrCorner1);
						  	gtk_box_pack_start(GTK_BOX(hboxCorner), vrCorner1,FALSE,TRUE,0);
						  	GtkWidget* vboxCornerFrom = gtk_vbox_new(FALSE,0);
						  	gtk_widget_show(vboxCornerFrom);
						  	gtk_box_pack_start(GTK_BOX(hboxCorner), vboxCornerFrom,FALSE,TRUE,0);
						  	GtkWidget* vrCorner2 = gtk_vseparator_new();
						  	gtk_widget_show(vrCorner2);
						  	gtk_box_pack_start(GTK_BOX(hboxCorner), vrCorner2,FALSE,TRUE,0);
						  	GtkWidget* vboxCornerTo = gtk_vbox_new(FALSE,0);
						  	gtk_widget_show(vboxCornerTo);
						  	gtk_box_pack_start(GTK_BOX(hboxCorner), vboxCornerTo,FALSE,TRUE,0);

						  	GtkWidget* lbStartSteps = gtk_label_new("Start to step - ");
						  	gtk_widget_show(lbStartSteps);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerLabels), lbStartSteps,FALSE,TRUE,0);
						  	GtkWidget* vboxCornerInfo = gtk_vbox_new(FALSE,0);
						  	gtk_widget_show(vboxCornerInfo);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerLabels), vboxCornerInfo,TRUE,TRUE,0);
						  	lbStartCorners = gtk_label_new("CORNER/FROM");
						  	gtk_widget_show(lbStartCorners);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerInfo), lbStartCorners,TRUE,TRUE,0);
						  	GtkWidget* hrCorner1 = gtk_hseparator_new();
						  	gtk_widget_show(hrCorner1);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerInfo), hrCorner1,FALSE,TRUE,0);
						  	lbEndCorners = gtk_label_new("CORNER/TO");
						  	gtk_widget_show(lbEndCorners);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerInfo), lbEndCorners,TRUE,TRUE,0);


						  	GtkWidget* lbStartStepsFrom = gtk_label_new("From:");
						  	gtk_widget_show(lbStartStepsFrom);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerFrom), lbStartStepsFrom,FALSE,TRUE,0);

						  	GtkWidget* tblSelectFromCorners = gtk_table_new(3,3,FALSE);
						  	gtk_widget_show(tblSelectFromCorners);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerFrom), tblSelectFromCorners,FALSE,TRUE,0);

						  	GSList *listSelectCorners=NULL;
						  	rbCornerTopLeft = gtk_radio_button_new(NULL);
						  	listSelectCorners = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbCornerTopLeft));
						  	rbCornerTopRight = gtk_radio_button_new(listSelectCorners);
						  	listSelectCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbCornerTopRight));
						  	rbCornerCenter = gtk_radio_button_new(listSelectCorners);
						  	listSelectCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbCornerCenter));
						  	rbCornerBottomLeft = gtk_radio_button_new(listSelectCorners);
						  	listSelectCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbCornerBottomLeft));
						  	rbCornerBottomRight  = gtk_radio_button_new(listSelectCorners);
						  	listSelectCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbCornerBottomRight));
						  	gtk_widget_show(rbCornerTopLeft);
						  	gtk_widget_show(rbCornerTopRight);
						  	gtk_widget_show(rbCornerCenter);
						  	gtk_widget_show(rbCornerBottomLeft);
						  	gtk_widget_show(rbCornerBottomRight);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectFromCorners), rbCornerTopLeft,0,1,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectFromCorners), rbCornerTopRight,2,3,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectFromCorners), rbCornerCenter,1,2,1,2);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectFromCorners), rbCornerBottomLeft,0,1,2,3);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectFromCorners), rbCornerBottomRight,2,3,2,3);

						  	g_signal_connect(rbCornerTopLeft, "toggled",
						  					  G_CALLBACK (on_set_start_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_LEFT));
						  	g_signal_connect(rbCornerTopRight, "toggled",
						  					  G_CALLBACK (on_set_start_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_RIGHT));
						  	g_signal_connect(rbCornerCenter, "toggled",
						  					  G_CALLBACK (on_set_start_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)CENTER_CENTER));
						  	g_signal_connect(rbCornerBottomLeft, "toggled",
						  					  G_CALLBACK (on_set_start_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_LEFT));
						  	g_signal_connect(rbCornerBottomRight, "toggled",
						  					  G_CALLBACK (on_set_start_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_RIGHT));

						  	GtkWidget* lbStartStepsTo = gtk_label_new("To:");
						  	gtk_widget_show(lbStartStepsTo);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerTo), lbStartStepsTo,FALSE,TRUE,0);

						  	GtkWidget* tblSelectToCorners = gtk_table_new(3,3,FALSE);
						  	gtk_widget_show(tblSelectToCorners);
						  	gtk_box_pack_start(GTK_BOX(vboxCornerTo), tblSelectToCorners,FALSE,TRUE,0);

						  	GSList *listSelectToCorners=NULL;
						  	rbEndCornerTopLeft = gtk_radio_button_new(NULL);
						  	listSelectToCorners = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbEndCornerTopLeft));
						  	rbEndCornerTopRight = gtk_radio_button_new(listSelectToCorners);
						  	listSelectToCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbEndCornerTopRight));
						  	rbEndCornerCenter = gtk_radio_button_new(listSelectToCorners);
						  	listSelectToCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbEndCornerCenter));
						  	rbEndCornerBottomLeft = gtk_radio_button_new(listSelectToCorners);
						  	listSelectToCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbEndCornerBottomLeft));
						  	rbEndCornerBottomRight  = gtk_radio_button_new(listSelectToCorners);
						  	listSelectToCorners = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbEndCornerBottomRight));
						  	gtk_widget_show(rbEndCornerTopLeft);
						  	gtk_widget_show(rbEndCornerTopRight);
						  	gtk_widget_show(rbEndCornerCenter);
						  	gtk_widget_show(rbEndCornerBottomLeft);
						  	gtk_widget_show(rbEndCornerBottomRight);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectToCorners), rbEndCornerTopLeft,0,1,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectToCorners), rbEndCornerTopRight,2,3,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectToCorners), rbEndCornerCenter,1,2,1,2);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectToCorners), rbEndCornerBottomLeft,0,1,2,3);
						  	gtk_table_attach_defaults(GTK_TABLE(tblSelectToCorners), rbEndCornerBottomRight,2,3,2,3);

						  	g_signal_connect(rbEndCornerTopLeft, "toggled",
						  					  G_CALLBACK (on_set_end_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_LEFT));
						  	g_signal_connect(rbEndCornerTopRight, "toggled",
						  					  G_CALLBACK (on_set_end_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)TOP_RIGHT));
						  	g_signal_connect(rbEndCornerCenter, "toggled",
						  					  G_CALLBACK (on_set_end_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)CENTER_CENTER));
						  	g_signal_connect(rbEndCornerBottomLeft, "toggled",
						  					  G_CALLBACK (on_set_end_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_LEFT));
						  	g_signal_connect(rbEndCornerBottomRight, "toggled",
						  					  G_CALLBACK (on_set_end_corner_radio),
						  					  GINT_TO_POINTER((enum AUTO_COORD_TYPE)BOTTOM_RIGHT));

////////////////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////
				//Add Effects expander panels:
				//////////////////////////////////////////////////////////
				GtkWidget* epEffects = gtk_expander_new(
						"<span foreground='blue'><b>EFFECTS</b></span>"
						);
				gtk_expander_set_use_markup(GTK_EXPANDER(epEffects),TRUE);
				gtk_widget_show(epEffects);
				gtk_box_pack_start(GTK_BOX(vboxExpander), epEffects, FALSE, TRUE, 0);
				//Add alignment
				GtkWidget* alignmentEffects = gtk_alignment_new(
						0.5,
						0.5,
						1,
						1);
				gtk_alignment_set_padding(GTK_ALIGNMENT(alignmentEffects),0,0,6,6);
				gtk_widget_show(alignmentEffects);
				gtk_container_add(GTK_CONTAINER(epEffects), alignmentEffects);
				//Add vbox for frames
				GtkWidget* vboxEffects =  gtk_vbox_new (FALSE, 0);
				gtk_widget_show(vboxEffects);
				gtk_container_add(GTK_CONTAINER(alignmentEffects), vboxEffects);
				/*
				 * Add Transparency expander:
				 */
				GtkWidget* opacityExpander = gtk_expander_new(
						"<b>Transparency</b>"
						);
				gtk_expander_set_use_markup(GTK_EXPANDER(opacityExpander),TRUE);
				gtk_widget_show(opacityExpander);
				gtk_box_pack_start(GTK_BOX(vboxEffects), opacityExpander, FALSE, TRUE, 0);
				GtkWidget* alignmentTransparency = gtk_alignment_new(
										0.5,
										0.5,
										1,
										1);
				gtk_widget_show(alignmentTransparency);
				gtk_container_add(GTK_CONTAINER(opacityExpander), alignmentTransparency);
				GtkWidget* vboxTransparency =  gtk_vbox_new (FALSE, 0);
				gtk_widget_show(vboxTransparency);
				gtk_container_add(GTK_CONTAINER(alignmentTransparency), vboxTransparency);

				//Add frame for Transparency
				GtkWidget* frameEffectAlpha = gtk_frame_new("");
				gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameEffectAlpha))),"<b>Fixed Opacity</b>");
				gtk_widget_show(frameEffectAlpha);
				gtk_box_pack_start(GTK_BOX(vboxTransparency), frameEffectAlpha, TRUE, TRUE, 0);
				//Add alingment for frame
				GtkWidget* alingmentFrameEffectAlpha = gtk_alignment_new(
							  			  0.5,
							  			  0.5,
							  			  1,
							  			  1);
				gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameEffectAlpha),0,0,6,3);
				gtk_widget_show(alingmentFrameEffectAlpha);
				gtk_container_add(GTK_CONTAINER(frameEffectAlpha), alingmentFrameEffectAlpha);
					//Add table for frame:
			  	  GtkWidget* tblAlphaFixStep = gtk_table_new(1,3,FALSE);
			  	  gtk_table_set_col_spacings(GTK_TABLE(tblAlphaFixStep), 3);
			  	  gtk_widget_show(tblAlphaFixStep);
			  	  gtk_container_add(GTK_CONTAINER(alingmentFrameEffectAlpha), tblAlphaFixStep);
			  	  adjAlphaStep = gimp_scale_entry_new(
			  				   						  GTK_TABLE(tblAlphaFixStep), //table
			  				   						  0,			//column
			  				   						  0,			//row
			  				   						  "Opacity:",		//text
			  				   						  50,			//minimum horizontal size of the GtkHScale.
			  				   						  60,			//minimum horizontal size of the GtkSpinButton.
			  				   						  pl_vals.opacity,//The initial value
			  				   						  -100,			//The lower boundary
			  				   						  100,			//The upper boundary
			  				   						  1,			//The step increment
			  				   						  1,			//The page increment (??)
			  				   						  0,			//number of decimal digits
			  				   						  TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
			  				   						  0,			//spinbutton's lower boundary if constrain == FALSE
			  				   						  0,			//spinbutton's upper boundary if constrain == FALSE
			  				   						  "",	//A tooltip message for the scale and the spinbutton
			  				   						  NULL //The widgets' help_id
			  				   				  );
			  	  	g_signal_connect(adjAlphaStep, "value_changed",
			  				   				G_CALLBACK (gimp_int_adjustment_update),
			  				   					&pl_vals.opacity);
			  	  g_signal_connect(adjAlphaStep, "value_changed",
			  	  		G_CALLBACK (checkValues),
			  	  		 GINT_TO_POINTER(CHK_OPACITY));

				  	//Add frame for Random Opacity
				  	GtkWidget* frameAlphaRanStep = gtk_frame_new("");
				  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameAlphaRanStep))),"Random Opacity");
				  	gtk_widget_show(frameAlphaRanStep);
				  	gtk_box_pack_start(GTK_BOX(vboxTransparency), frameAlphaRanStep, TRUE, TRUE, 0);
				  	//Add alingment for frame
				  	GtkWidget* alingmentFrameAlphaRanStep = gtk_alignment_new(
				  			  0.5,
				  			  0.5,
				  			  1,
				  			  1);
				  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameAlphaRanStep),0,0,6,3);
				  	gtk_widget_show(alingmentFrameAlphaRanStep);
				  	gtk_container_add(GTK_CONTAINER(frameAlphaRanStep), alingmentFrameAlphaRanStep);
					  //Add table for frame:
				  	  GtkWidget* tblAlphaRanStep = gtk_table_new(1,4,FALSE);
				  	  gtk_table_set_col_spacings(GTK_TABLE(tblAlphaRanStep), 3);
				  	  gtk_widget_show(tblAlphaRanStep);
				  	  gtk_container_add(GTK_CONTAINER(alingmentFrameAlphaRanStep), tblAlphaRanStep);
				  	  GtkWidget* lbRanStepAlphaMin = gtk_label_new("Opacity min.:");
				  	  spbRanStepAlphaMin = gimp_spin_button_new(
				  			  &adjRanStepAlphaMin,
				  			  pl_vals.ran_step_opacity_min,
				  			  0, 100,
				  			  1, 1,
				  			  1,
				  			  10,
				  			  0);
				  	  GtkWidget* lbRanStepAlphaMax = gtk_label_new("Opacity max.:");
				  	  spbRanStepAlphaMax= gimp_spin_button_new(
				  			  &adjRanStepAlphaMax,
				  			  pl_vals.ran_step_opacity_max,
				  			0, 100,
				  			  1, 1,
				  			  1,
				  			  10,
				  			  0);
					  	gtk_widget_show(spbRanStepAlphaMin);
					  	gtk_widget_show(spbRanStepAlphaMax);

					  	gtk_widget_show(lbRanStepAlphaMin);
					  	gtk_widget_show(lbRanStepAlphaMax);

					  	gtk_table_attach_defaults(GTK_TABLE(tblAlphaRanStep), lbRanStepAlphaMin,0,1,0,1);
					  	gtk_table_attach_defaults(GTK_TABLE(tblAlphaRanStep), spbRanStepAlphaMin,1,2,0,1);
					  	gtk_table_attach_defaults(GTK_TABLE(tblAlphaRanStep), lbRanStepAlphaMax,2,3,0,1);
					  	gtk_table_attach_defaults(GTK_TABLE(tblAlphaRanStep), spbRanStepAlphaMax,3,4,0,1);

					  	g_signal_connect(adjRanStepAlphaMin, "value_changed",
					  	                      G_CALLBACK (gimp_int_adjustment_update),
					  	                      &pl_vals.ran_step_opacity_min);
					  	g_signal_connect(adjRanStepAlphaMax, "value_changed",
					  	                      G_CALLBACK (gimp_int_adjustment_update),
					  	                      &pl_vals.ran_step_opacity_max);

					  	g_signal_connect(adjRanStepAlphaMin, "value_changed",
					  			G_CALLBACK(checkValues),
					  			GINT_TO_POINTER(CHK_MIN_ALPHA));
					  	g_signal_connect(adjRanStepAlphaMax, "value_changed",
					  			G_CALLBACK(checkValues),
					  			GINT_TO_POINTER(CHK_MAX_ALPHA));

					  	/*
					  	 *
					  	 */
					  	GtkWidget* hrEffect01 = gtk_hseparator_new();
					  	gtk_widget_show(hrEffect01);
					  	gtk_box_pack_start(GTK_BOX(vboxEffects), hrEffect01, FALSE, TRUE, 0);

					  	/*
					  	 * Blur
					  	 */
						GtkWidget* blurExpander = gtk_expander_new(
								"<b>Blur</b>"
								);
						gtk_expander_set_use_markup(GTK_EXPANDER(blurExpander),TRUE);
						gtk_widget_show(blurExpander);
						gtk_box_pack_start(GTK_BOX(vboxEffects), blurExpander, FALSE, TRUE, 0);
						GtkWidget* alignmentBlur = gtk_alignment_new(
												0.5,
												0.5,
												1,
												1);
						gtk_widget_show(alignmentBlur);
						gtk_container_add(GTK_CONTAINER(blurExpander), alignmentBlur);
						GtkWidget* vboxBlur =  gtk_vbox_new (FALSE, 0);
						gtk_widget_show(vboxBlur);
						gtk_container_add(GTK_CONTAINER(alignmentBlur), vboxBlur);

					  	//Add frame for Blur
					  	GtkWidget* frameBlur = gtk_frame_new("");
					  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameBlur))),"Blur Steps");
					  	gtk_widget_show(frameBlur);
					  	gtk_box_pack_start(GTK_BOX(vboxBlur), frameBlur, TRUE, TRUE, 0);
					  	//Add alingment for frame
					  	GtkWidget* alingmentFrameBlur = gtk_alignment_new(
					  			  0.5,
					  			  0.5,
					  			  1,
					  			  1);
					  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameBlur),0,0,6,3);
					  	gtk_widget_show(alingmentFrameBlur);
					  	gtk_container_add(GTK_CONTAINER(frameBlur), alingmentFrameBlur);
						  //Add table for frame:
					  	  GtkWidget* tblBlure = gtk_table_new(1,4,FALSE);
					  	  gtk_table_set_col_spacings(GTK_TABLE(tblBlure), 3);
					  	  gtk_widget_show(tblBlure);
					  	  gtk_container_add(GTK_CONTAINER(alingmentFrameBlur), tblBlure);

					  	adjBlurRadius = gimp_scale_entry_new(
									  				 GTK_TABLE(tblBlure), //table
									  				 0,			//column
									  				 0,			//row
									  				 "Hue:",	//text
									  				 50,		//minimum horizontal size of the GtkHScale.
									  				 60,		//minimum horizontal size of the GtkSpinButton.
									  				pl_vals.blur_radius,//The initial value
									  				0,			//The lower boundary
									  				350,			//The upper boundary
									  				1,			//The step increment
									  				1,			//The page increment (??)
									  				0,			//number of decimal digits
									  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
									  				0,			//spinbutton's lower boundary if constrain == FALSE
									  				0,			//spinbutton's upper boundary if constrain == FALSE
									  				"",	//A tooltip message for the scale and the spinbutton
									  				NULL //The widgets' help_id
							);


					  	g_signal_connect(adjBlurRadius, "value_changed",
					  	                      G_CALLBACK (gimp_double_adjustment_update),
					  	                      &pl_vals.blur_radius);
					  	  g_signal_connect(adjBlurRadius, "value_changed",
					  	  		G_CALLBACK (checkValues),
					  	  		 GINT_TO_POINTER(CHK_BLUR));

					  	//Add frame for Random Blur
					  	GtkWidget* frameRandomBlur = gtk_frame_new("");
					  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameRandomBlur))),"Random Blur");
					  	gtk_widget_show(frameRandomBlur);
					  	gtk_box_pack_start(GTK_BOX(vboxBlur), frameRandomBlur, TRUE, TRUE, 0);
					  	//Add alingment for frame
					  	GtkWidget* alingmentFrameRandomBlur = gtk_alignment_new(
					  			  0.5,
					  			  0.5,
					  			  1,
					  			  1);
					  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameRandomBlur),0,0,6,3);
					  	gtk_widget_show(alingmentFrameRandomBlur);
					  	gtk_container_add(GTK_CONTAINER(frameRandomBlur), alingmentFrameRandomBlur);
						  //Add table for frame:
					  	  GtkWidget* tblRandomBlur = gtk_table_new(1,4,FALSE);
					  	  gtk_table_set_col_spacings(GTK_TABLE(tblRandomBlur), 3);
					  	  gtk_widget_show(tblRandomBlur);
					  	  gtk_container_add(GTK_CONTAINER(alingmentFrameRandomBlur), tblRandomBlur);
					  	  GtkWidget* lbRanBlurMin = gtk_label_new("Radius min.:");
					  	  spbRanBlurMin = gimp_spin_button_new(
					  			  &adjRanBlurMin,
					  			  pl_vals.random_blur_min,
					  			  0, 350,
					  			  1, 1,
					  			  1,
					  			  10,
					  			  0);
					  	  GtkWidget* lbRanBlurMax = gtk_label_new("Radius max.:");
					  	  spbRanBlurMax= gimp_spin_button_new(
					  			  &adjRanBlurMax,
					  			  pl_vals.random_blur_max,
					  			0, 350,
					  			  1, 1,
					  			  1,
					  			  10,
					  			  0);
						  	gtk_widget_show(lbRanBlurMin);
						  	gtk_widget_show(spbRanBlurMin);

						  	gtk_widget_show(lbRanBlurMax);
						  	gtk_widget_show(spbRanBlurMax);

						  	gtk_table_attach_defaults(GTK_TABLE(tblRandomBlur), lbRanBlurMin,0,1,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblRandomBlur), spbRanBlurMin,1,2,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblRandomBlur), lbRanBlurMax,2,3,0,1);
						  	gtk_table_attach_defaults(GTK_TABLE(tblRandomBlur), spbRanBlurMax,3,4,0,1);

						  	g_signal_connect(adjRanBlurMin, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.random_blur_min);
						  	g_signal_connect(adjRanBlurMax, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.random_blur_max);

						  	g_signal_connect(adjRanBlurMin, "value_changed",
						  			G_CALLBACK(checkValues),
						  			GINT_TO_POINTER(CHK_MIN_BLUR));
						  	g_signal_connect(adjRanBlurMax, "value_changed",
						  			G_CALLBACK(checkValues),
						  			GINT_TO_POINTER(CHK_MAX_BLUR));
						  	/*
						  	 *
						  	 */
						  	GtkWidget* hrEffect02 = gtk_hseparator_new();
						  	gtk_widget_show(hrEffect02);
						  	gtk_box_pack_start(GTK_BOX(vboxEffects), hrEffect02, FALSE, TRUE, 0);

						  	/*
						  	 *Colorize
						  	 */
							GtkWidget* colorizeExpander = gtk_expander_new(
									"<b>Colorize</b>"
									);
							gtk_expander_set_use_markup(GTK_EXPANDER(colorizeExpander),TRUE);
							gtk_widget_show(colorizeExpander);
							gtk_box_pack_start(GTK_BOX(vboxEffects), colorizeExpander, FALSE, TRUE, 0);
							GtkWidget* alignmentColorize = gtk_alignment_new(
													0.5,
													0.5,
													1,
													1);
							gtk_widget_show(alignmentColorize);
							gtk_container_add(GTK_CONTAINER(colorizeExpander), alignmentColorize);
							GtkWidget* vboxColorize =  gtk_vbox_new (FALSE, 0);
							gtk_widget_show(vboxColorize);
							gtk_container_add(GTK_CONTAINER(alignmentColorize), vboxColorize);

						  	//Add frame for Colorize
						  	GtkWidget* frameColorize = gtk_frame_new("");
						  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameColorize))),"Colorize Setting");
						  	gtk_widget_show(frameColorize);
						  	gtk_box_pack_start(GTK_BOX(vboxColorize), frameColorize, TRUE, TRUE, 0);

						  	//Add alingment for frame
						  	GtkWidget* alingmentFrameColorize = gtk_alignment_new(
						  			  0.5,
						  			  0.5,
						  			  1,
						  			  1);
						  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameColorize),0,0,6,3);
						  	gtk_widget_show(alingmentFrameColorize);
						  	gtk_container_add(GTK_CONTAINER(frameColorize), alingmentFrameColorize);
							  //Add table for frame:
						  	  GtkWidget* tblColorize = gtk_table_new(1,4,FALSE);
						  	  gtk_table_set_col_spacings(GTK_TABLE(tblColorize), 3);
						  	  gtk_widget_show(tblColorize);
						  	  gtk_container_add(GTK_CONTAINER(alingmentFrameColorize), tblColorize);

						  	adjColorizeHue = gimp_scale_entry_new(
									  				 GTK_TABLE(tblColorize), //table
									  				 0,			//column
									  				 0,			//row
									  				 "Hue:",	//text
									  				 50,		//minimum horizontal size of the GtkHScale.
									  				 60,		//minimum horizontal size of the GtkSpinButton.
									  				pl_vals.colorize_hue,//The initial value
									  				0,			//The lower boundary
									  				360,			//The upper boundary
									  				1,			//The step increment
									  				1,			//The page increment (??)
									  				0,			//number of decimal digits
									  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
									  				0,			//spinbutton's lower boundary if constrain == FALSE
									  				0,			//spinbutton's upper boundary if constrain == FALSE
									  				"",	//A tooltip message for the scale and the spinbutton
									  				NULL //The widgets' help_id
							);


						  	g_signal_connect(adjColorizeHue, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.colorize_hue);

						  	  g_signal_connect(adjColorizeHue, "value_changed",
						  	  		G_CALLBACK (checkValues),
						  	  		 GINT_TO_POINTER(CHK_COLORIZE));

						  	//Add frame for Random Colorize
						  	GtkWidget* frameRandomColorize = gtk_frame_new("");
						  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameRandomColorize))),"Random Colorize");
						  	gtk_widget_show(frameRandomColorize);
						  	gtk_box_pack_start(GTK_BOX(vboxColorize), frameRandomColorize, TRUE, TRUE, 0);
						  	//Add alingment for frame
						  	GtkWidget* alingmentFrameRandomColorize = gtk_alignment_new(
						  			  0.5,
						  			  0.5,
						  			  1,
						  			  1);
						  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameRandomColorize),0,0,6,3);
						  	gtk_widget_show(alingmentFrameRandomColorize);
						  	gtk_container_add(GTK_CONTAINER(frameRandomColorize), alingmentFrameRandomColorize);
							  //Add table for frame:
						  	  GtkWidget* tblRandomHue = gtk_table_new(1,4,FALSE);
						  	  gtk_table_set_col_spacings(GTK_TABLE(tblRandomHue), 3);
						  	  gtk_widget_show(tblRandomHue);
						  	  gtk_container_add(GTK_CONTAINER(alingmentFrameRandomColorize), tblRandomHue);
						  	  GtkWidget* lbRanHueMin = gtk_label_new("Hue min.:");
						  	  spbRanHueMin = gimp_spin_button_new(
						  			  &adjRanHueMin,
						  			  pl_vals.random_hue_min,
						  			  0, 360,
						  			  1, 1,
						  			  1,
						  			  10,
						  			  0);
						  	  GtkWidget* lbRanHueMax = gtk_label_new("Hue max.:");
						  	  spbRanHueMax= gimp_spin_button_new(
						  			  &adjRanHueMax,
						  			  pl_vals.random_hue_max,
						  			0, 360,
						  			  1, 1,
						  			  1,
						  			  10,
						  			  0);
							  	gtk_widget_show(lbRanHueMin);
							  	gtk_widget_show(spbRanHueMin);

							  	gtk_widget_show(lbRanHueMax);
							  	gtk_widget_show(spbRanHueMax);

							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomHue), lbRanHueMin,0,1,0,1);
							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomHue), spbRanHueMin,1,2,0,1);
							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomHue), lbRanHueMax,2,3,0,1);
							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomHue), spbRanHueMax,3,4,0,1);

							  	g_signal_connect(adjRanHueMin, "value_changed",
							  	                      G_CALLBACK (gimp_int_adjustment_update),
							  	                      &pl_vals.random_hue_min);
							  	g_signal_connect(adjRanHueMax, "value_changed",
							  	                      G_CALLBACK (gimp_int_adjustment_update),
							  	                      &pl_vals.random_hue_max);

							  	g_signal_connect(adjRanHueMin, "value_changed",
							  			G_CALLBACK(checkValues),
							  			GINT_TO_POINTER(CHK_MIN_HUE));
							  	g_signal_connect(adjRanHueMax, "value_changed",
							  			G_CALLBACK(checkValues),
							  			GINT_TO_POINTER(CHK_MAX_HUE));


							  	//Add frame for Colorize More Setting
							  	GtkWidget* frameColorizeMore = gtk_frame_new("");
							  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameColorizeMore))),"Colorize More Setting");
							  	gtk_widget_show(frameColorizeMore);
							  	gtk_box_pack_start(GTK_BOX(vboxColorize), frameColorizeMore, TRUE, TRUE, 0);

							  	//Add alingment for frame
							  	GtkWidget* alingmentFrameColorizeMore = gtk_alignment_new(
							  			  0.5,
							  			  0.5,
							  			  1,
							  			  1);
							  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameColorizeMore),0,0,6,3);
							  	gtk_widget_show(alingmentFrameColorizeMore);
							  	gtk_container_add(GTK_CONTAINER(frameColorizeMore), alingmentFrameColorizeMore);
								  //Add table for frame:
							  	  GtkWidget* tblColorizeMore = gtk_table_new(2,4,FALSE);
							  	  gtk_table_set_col_spacings(GTK_TABLE(tblColorizeMore), 3);
							  	  gtk_widget_show(tblColorizeMore);
							  	  gtk_container_add(GTK_CONTAINER(alingmentFrameColorizeMore), tblColorizeMore);

							  	adjColorizeSat = gimp_scale_entry_new(
									  				 GTK_TABLE(tblColorizeMore), //table
									  				 0,			//column
									  				 0,			//row
									  				 "Saturation:",	//text
									  				 50,		//minimum horizontal size of the GtkHScale.
									  				 60,		//minimum horizontal size of the GtkSpinButton.
									  				pl_vals.colorize_sat,//The initial value
									  				0,			//The lower boundary
									  				100,			//The upper boundary
									  				1,			//The step increment
									  				1,			//The page increment (??)
									  				0,			//number of decimal digits
									  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
									  				0,			//spinbutton's lower boundary if constrain == FALSE
									  				0,			//spinbutton's upper boundary if constrain == FALSE
									  				"",	//A tooltip message for the scale and the spinbutton
									  				NULL //The widgets' help_id
									);

							  	adjColorizeLight = gimp_scale_entry_new(
									  				 GTK_TABLE(tblColorizeMore), //table
									  				 0,			//column
									  				 1,			//row
									  				 "Lightness:",	//text
									  				 50,		//minimum horizontal size of the GtkHScale.
									  				 60,		//minimum horizontal size of the GtkSpinButton.
									  				pl_vals.colorize_light,//The initial value
									  				-100,			//The lower boundary
									  				100,			//The upper boundary
									  				1,			//The step increment
									  				1,			//The page increment (??)
									  				0,			//number of decimal digits
									  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
									  				0,			//spinbutton's lower boundary if constrain == FALSE
									  				0,			//spinbutton's upper boundary if constrain == FALSE
									  				"",	//A tooltip message for the scale and the spinbutton
									  				NULL //The widgets' help_id
									);


							  	g_signal_connect(adjColorizeHue, "value_changed",
							  	                      G_CALLBACK (gimp_int_adjustment_update),
							  	                      &pl_vals.colorize_hue);

							  	  g_signal_connect(adjColorizeHue, "value_changed",
							  	  		G_CALLBACK (checkValues),
							  	  		 GINT_TO_POINTER(CHK_COLORIZE_SAT));

								  g_signal_connect(adjColorizeLight, "value_changed",
								  	                      G_CALLBACK (gimp_int_adjustment_update),
								  	                      &pl_vals.colorize_light);

								  g_signal_connect(adjColorizeLight, "value_changed",
								  	  		G_CALLBACK (checkValues),
								  	  		 GINT_TO_POINTER(CHK_COLORIZE_LIGHT));

						  	/*
						  	 *
						  	 */
						  	GtkWidget* hrEffect03 = gtk_hseparator_new();
						  	gtk_widget_show(hrEffect03);
						  	gtk_box_pack_start(GTK_BOX(vboxEffects), hrEffect03, FALSE, TRUE, 0);

						  	/*
						  	 *Spread
						  	 */
							GtkWidget* spreadExpander = gtk_expander_new(
									"<b>Noise Spread</b>"
									);
							gtk_expander_set_use_markup(GTK_EXPANDER(spreadExpander),TRUE);
							gtk_widget_show(spreadExpander);
							gtk_box_pack_start(GTK_BOX(vboxEffects), spreadExpander, FALSE, TRUE, 0);
							GtkWidget* alignmentSpread = gtk_alignment_new(
													0.5,
													0.5,
													1,
													1);
							gtk_widget_show(alignmentSpread);
							gtk_container_add(GTK_CONTAINER(spreadExpander), alignmentSpread);
							GtkWidget* vboxSpread =  gtk_vbox_new (FALSE, 0);
							gtk_widget_show(vboxSpread);
							gtk_container_add(GTK_CONTAINER(alignmentSpread), vboxSpread);

						  	//Add frame for Spread
						  	GtkWidget* frameSpread = gtk_frame_new("");
						  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameSpread))),"Spread Setting");
						  	gtk_widget_show(frameSpread);
						  	gtk_box_pack_start(GTK_BOX(vboxSpread), frameSpread, TRUE, TRUE, 0);
						  	//Add alingment for frame
						  	GtkWidget* alingmentFrameSpread = gtk_alignment_new(
						  			  0.5,
						  			  0.5,
						  			  1,
						  			  1);
						  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameSpread),0,0,6,3);
						  	gtk_widget_show(alingmentFrameSpread);
						  	gtk_container_add(GTK_CONTAINER(frameSpread), alingmentFrameSpread);
							  //Add table for frame:
						  	  GtkWidget* tblSpread = gtk_table_new(1,4,FALSE);
						  	  gtk_table_set_col_spacings(GTK_TABLE(tblSpread), 3);
						  	  gtk_widget_show(tblSpread);
						  	  gtk_container_add(GTK_CONTAINER(alingmentFrameSpread), tblSpread);

						  	adjSpreadSize = gimp_scale_entry_new(
							  				 GTK_TABLE(tblSpread), //table
							  				 0,			//column
							  				 1,			//row
							  				 "Radius:",	//text
							  				 50,		//minimum horizontal size of the GtkHScale.
							  				 60,		//minimum horizontal size of the GtkSpinButton.
							  				pl_vals.spread_radius,//The initial value
							  				0,			//The lower boundary
							  				350,			//The upper boundary
							  				1,			//The step increment
							  				1,			//The page increment (??)
							  				0,			//number of decimal digits
							  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
							  				0,			//spinbutton's lower boundary if constrain == FALSE
							  				0,			//spinbutton's upper boundary if constrain == FALSE
							  				"",	//A tooltip message for the scale and the spinbutton
							  				NULL //The widgets' help_id
							  );

						  	g_signal_connect(adjSpreadSize, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.spread_radius);

						  	  g_signal_connect(adjSpreadSize, "value_changed",
						  	  		G_CALLBACK (checkValues),
						  	  		 GINT_TO_POINTER(CHK_SPREAD));

						  	//Add frame for Random Spread
						  	GtkWidget* frameRandomSpread = gtk_frame_new("");
						  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameRandomSpread))),"Random Spread");
						  	gtk_widget_show(frameRandomSpread);
						  	gtk_box_pack_start(GTK_BOX(vboxSpread), frameRandomSpread, TRUE, TRUE, 0);
						  	//Add alingment for frame
						  	GtkWidget* alingmentFrameRandomSpread = gtk_alignment_new(
						  			  0.5,
						  			  0.5,
						  			  1,
						  			  1);
						  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameRandomSpread),0,0,6,3);
						  	gtk_widget_show(alingmentFrameRandomSpread);
						  	gtk_container_add(GTK_CONTAINER(frameRandomSpread), alingmentFrameRandomSpread);
							  //Add table for frame:
						  	  GtkWidget* tblRandomSpead = gtk_table_new(1,4,FALSE);
						  	  gtk_table_set_col_spacings(GTK_TABLE(tblRandomSpead), 3);
						  	  gtk_widget_show(tblRandomSpead);
						  	  gtk_container_add(GTK_CONTAINER(alingmentFrameRandomSpread), tblRandomSpead);
						  	  GtkWidget* lbRanSpreadMin = gtk_label_new("Radius min.:");
						  	  spbRanSpreadMin = gimp_spin_button_new(
						  			  &adjRanSpreadMin,
						  			  pl_vals.random_spread_min,
						  			  0, 350,
						  			  1, 1,
						  			  1,
						  			  10,
						  			  0);
						  	  GtkWidget* lbRanSpreadMax = gtk_label_new("Radius max.:");
						  	  spbRanSpreadMax= gimp_spin_button_new(
						  			  &adjRanSpreadMax,
						  			  pl_vals.random_spread_max,
						  			0, 350,
						  			  1, 1,
						  			  1,
						  			  10,
						  			  0);
							  	gtk_widget_show(lbRanSpreadMin);
							  	gtk_widget_show(spbRanSpreadMin);

							  	gtk_widget_show(lbRanSpreadMax);
							  	gtk_widget_show(spbRanSpreadMax);

							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomSpead), lbRanSpreadMin,0,1,0,1);
							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomSpead), spbRanSpreadMin,1,2,0,1);
							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomSpead), lbRanSpreadMax,2,3,0,1);
							  	gtk_table_attach_defaults(GTK_TABLE(tblRandomSpead), spbRanSpreadMax,3,4,0,1);

							  	g_signal_connect(adjRanSpreadMin, "value_changed",
							  	                      G_CALLBACK (gimp_int_adjustment_update),
							  	                      &pl_vals.random_spread_min);
							  	g_signal_connect(adjRanSpreadMax, "value_changed",
							  	                      G_CALLBACK (gimp_int_adjustment_update),
							  	                      &pl_vals.random_spread_max);

							  	g_signal_connect(adjRanSpreadMin, "value_changed",
							  			G_CALLBACK(checkValues),
							  			GINT_TO_POINTER(CHK_MIN_SPREAD));
							  	g_signal_connect(adjRanSpreadMax, "value_changed",
							  			G_CALLBACK(checkValues),
							  			GINT_TO_POINTER(CHK_MAX_SPREAD));
						  	/*
						  	 *
						  	 */
						  	GtkWidget* hrEffect04 = gtk_hseparator_new();
						  	gtk_widget_show(hrEffect04);
						  	gtk_box_pack_start(GTK_BOX(vboxEffects), hrEffect04, FALSE, TRUE, 0);

						  	/*
						  	 * Drop Shadow
						  	 */
							GtkWidget* shadowExpander = gtk_expander_new(
									"<b>Drop Shadow</b>"
									);
							gtk_expander_set_use_markup(GTK_EXPANDER(shadowExpander),TRUE);
							gtk_widget_show(shadowExpander);
							gtk_box_pack_start(GTK_BOX(vboxEffects), shadowExpander, FALSE, TRUE, 0);
							GtkWidget* alignmentShadow = gtk_alignment_new(
													0.5,
													0.5,
													1,
													1);
							gtk_widget_show(alignmentShadow);
							gtk_container_add(GTK_CONTAINER(shadowExpander), alignmentShadow);
							GtkWidget* vboxShadow =  gtk_vbox_new (FALSE, 0);
							gtk_widget_show(vboxShadow);
							gtk_container_add(GTK_CONTAINER(alignmentShadow), vboxShadow);

						  	//Add frame for Shadow
						  	GtkWidget* frameShadow = gtk_frame_new("");
						  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameShadow))),"Shadow Setting");
						  	gtk_widget_show(frameShadow);
						  	gtk_box_pack_start(GTK_BOX(vboxShadow), frameShadow, TRUE, TRUE, 0);
						  	//Add alingment for frame
						  	GtkWidget* alingmentFrameShadow = gtk_alignment_new(
						  			  0.5,
						  			  0.5,
						  			  1,
						  			  1);
						  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameShadow),0,0,6,3);
						  	gtk_widget_show(alingmentFrameShadow);
						  	gtk_container_add(GTK_CONTAINER(frameShadow), alingmentFrameShadow);
						  	GtkWidget* vboxShadowIn = gtk_vbox_new (FALSE, 0);
						  	gtk_widget_show(vboxShadowIn);
						  	gtk_container_add(GTK_CONTAINER(alingmentFrameShadow), vboxShadowIn);


						  	GtkWidget* tblShadow3 = gtk_table_new(1,3,FALSE);
						  	gtk_table_set_col_spacings(GTK_TABLE(tblShadow3), 3);
						  	gtk_widget_show(tblShadow3);
						  	gtk_box_pack_end(GTK_BOX(vboxShadowIn), tblShadow3, TRUE, TRUE, 0);

						  	adjShadowOpacity = gimp_scale_entry_new(
						  				 GTK_TABLE(tblShadow3), //table
						  				 0,			//column
						  				 1,			//row
						  				 "Opacity:",	//text
						  				 50,		//minimum horizontal size of the GtkHScale.
						  				 60,		//minimum horizontal size of the GtkSpinButton.
						  				pl_vals.shadow_opacity,//The initial value
						  				0,			//The lower boundary
						  				100,			//The upper boundary
						  				1,			//The step increment
						  				1,			//The page increment (??)
						  				0,			//number of decimal digits
						  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
						  				0,			//spinbutton's lower boundary if constrain == FALSE
						  				0,			//spinbutton's upper boundary if constrain == FALSE
						  				"",	//A tooltip message for the scale and the spinbutton
						  				NULL //The widgets' help_id
						  				);
						    g_signal_connect(adjShadowOpacity, "value_changed",
						    						  	     G_CALLBACK (gimp_int_adjustment_update),
						    						  	     &pl_vals.shadow_opacity);

							  //Add table for frame:
						  	  GtkWidget* tblShadow = gtk_table_new(4,3,FALSE);
						  	  gtk_table_set_col_spacings(GTK_TABLE(tblShadow), 3);
						  	  gtk_widget_show(tblShadow);
						  	gtk_box_pack_start(GTK_BOX(vboxShadowIn), tblShadow, TRUE, TRUE, 0);

						  	adjShadowSize = gimp_scale_entry_new(
						  				 GTK_TABLE(tblShadow), //table
						  				 0,			//column
						  				 0,			//row
						  				 "Size:",	//text
						  				 50,		//minimum horizontal size of the GtkHScale.
						  				 60,		//minimum horizontal size of the GtkSpinButton.
						  				pl_vals.shadow_size,//The initial value
						  				0,			//The lower boundary
						  				600,			//The upper boundary
						  				1,			//The step increment
						  				1,			//The page increment (??)
						  				0,			//number of decimal digits
						  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
						  				0,			//spinbutton's lower boundary if constrain == FALSE
						  				0,			//spinbutton's upper boundary if constrain == FALSE
						  				"",	//A tooltip message for the scale and the spinbutton
						  				NULL //The widgets' help_id
						  				);


						  	g_signal_connect(adjShadowSize, "value_changed",
						  	                      G_CALLBACK (gimp_int_adjustment_update),
						  	                      &pl_vals.shadow_size);

						  	adjShadowAngle = gimp_scale_entry_new(
						  				 GTK_TABLE(tblShadow), //table
						  				 0,			//column
						  				 2,			//row
						  				 "Angle:",	//text
						  				 50,		//minimum horizontal size of the GtkHScale.
						  				 60,		//minimum horizontal size of the GtkSpinButton.
						  				pl_vals.shadow_angle,//The initial value
						  				-180,			//The lower boundary
						  				180,			//The upper boundary
						  				1,			//The step increment
						  				1,			//The page increment (??)
						  				0,			//number of decimal digits
						  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
						  				0,			//spinbutton's lower boundary if constrain == FALSE
						  				0,			//spinbutton's upper boundary if constrain == FALSE
						  				"",	//A tooltip message for the scale and the spinbutton
						  				NULL //The widgets' help_id
						  				);

						  	adjShadowDistance = gimp_scale_entry_new(
						  				 GTK_TABLE(tblShadow), //table
						  				 0,			//column
						  				 1,			//row
						  				 "Distance:",	//text
						  				 50,		//minimum horizontal size of the GtkHScale.
						  				 60,		//minimum horizontal size of the GtkSpinButton.
						  				pl_vals.shadow_distance,//The initial value
						  				0,			//The lower boundary
						  				250,			//The upper boundary
						  				1,			//The step increment
						  				1,			//The page increment (??)
						  				0,			//number of decimal digits
						  				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
						  				0,			//spinbutton's lower boundary if constrain == FALSE
						  				0,			//spinbutton's upper boundary if constrain == FALSE
						  				"",	//A tooltip message for the scale and the spinbutton
						  				NULL //The widgets' help_id
						  				);

						  	g_signal_connect (adjShadowAngle, "value_changed",
						  						G_CALLBACK (gimp_int_adjustment_update),
						  						&pl_vals.shadow_angle);
						  	g_signal_connect (adjShadowDistance, "value_changed",
						  						G_CALLBACK (gimp_int_adjustment_update),
						  						&pl_vals.shadow_distance);

						  	GtkWidget* tblShadow2 = gtk_table_new(1,4,FALSE);
						  	gtk_table_set_col_spacings(GTK_TABLE(tblShadow2), 3);
						  	gtk_widget_show(tblShadow2);
						  	gtk_box_pack_end(GTK_BOX(vboxShadowIn), tblShadow2, TRUE, TRUE, 0);

						  	GtkWidget* lbShadowColor = gtk_label_new("Color:");
						  	gtk_misc_set_alignment(GTK_MISC(lbShadowColor),0,0.5);
						  	btShadowColor = gimp_color_button_new("Shadow Color",
						  			20, 16,
						  			&pl_vals.shadow_color,
						  			GIMP_COLOR_AREA_FLAT);
						  	gimp_color_button_set_update (GIMP_COLOR_BUTTON (btShadowColor), TRUE);
						  	gtk_widget_show(btShadowColor); gtk_widget_show(lbShadowColor);
						  	gtk_table_attach(GTK_TABLE(tblShadow2),GTK_WIDGET(lbShadowColor),
						  							                      0,1,0,1,
						  							                      GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,3,3);
						  	gtk_table_attach(GTK_TABLE(tblShadow2),GTK_WIDGET(btShadowColor),
						  							                      1,2,0,1,
						  							                      GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,3,3);

						    g_signal_connect (btShadowColor, "color-changed",
						                      G_CALLBACK (gimp_color_button_get_color),
						                      &pl_vals.shadow_color);


////////////////////////////////////////////////////////////////////////////////////////////
							/////////////////////////////////////////////////////////
							//Add Animation expander panels:
							//////////////////////////////////////////////////////////
							GtkWidget* epAnimate = gtk_expander_new(
									"<span foreground='#590000'><b>ANIMATE</b></span>"
									);
							gtk_expander_set_use_markup(GTK_EXPANDER(epAnimate),TRUE);
							gtk_widget_show(epAnimate);
							gtk_box_pack_start(GTK_BOX(vboxExpander), epAnimate, FALSE, TRUE, 0);
							//Add alignment
							GtkWidget* alignmentAnimate = gtk_alignment_new(
									0.5,
									0.5,
									1,
									1);
							gtk_alignment_set_padding(GTK_ALIGNMENT(alignmentAnimate),0,0,6,6);
							gtk_widget_show(alignmentAnimate);
							gtk_container_add(GTK_CONTAINER(epAnimate), alignmentAnimate);
							//Add vbox for frames
							GtkWidget* vboxAnimate =  gtk_vbox_new (FALSE, 0);
							gtk_widget_show(vboxAnimate);
							gtk_container_add(GTK_CONTAINER(alignmentAnimate), vboxAnimate);

							chkEnableAnimate = gtk_check_button_new_with_label("On/Off");
							gtk_widget_show(chkEnableAnimate);
							gtk_box_pack_start(GTK_BOX(vboxAnimate), chkEnableAnimate, TRUE, TRUE, 6);
							g_signal_connect(chkEnableAnimate, "toggled",
							                  				 G_CALLBACK (on_set_animate_on_radio),
							                  				 NULL);
							//Add frame for Animate options
						  	frameAnimate = gtk_frame_new("");
						  	gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameAnimate))),"<b>Animation Setting</b>");
						  	gtk_widget_show(frameAnimate);
						  	gtk_box_pack_start(GTK_BOX(vboxAnimate), frameAnimate, TRUE, TRUE, 0);
						  	//Add alingment for frame
						  	GtkWidget* alingmentFrameAnimate = gtk_alignment_new(
						  			  0.5,
						  			  0.5,
						  			  1,
						  			  1);
						  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameAnimate),0,0,6,3);
						  	gtk_widget_show(alingmentFrameAnimate);
						  	gtk_container_add(GTK_CONTAINER(frameAnimate), alingmentFrameAnimate);
							  //Add table for frame:
						  	  GtkWidget* tblAnimate = gtk_table_new(4,3,FALSE);
						  	  gtk_table_set_col_spacings(GTK_TABLE(tblAnimate), 3);
						  	  gtk_widget_show(tblAnimate);
						  	  gtk_container_add(GTK_CONTAINER(alingmentFrameAnimate), tblAnimate);


						  	GtkWidget* lbModeL = gtk_label_new("Mode Layer:");
						  	GtkWidget* lbSpeadL = gtk_label_new("Speed in ms:");
						  	gtk_widget_show(lbModeL); gtk_widget_show(lbSpeadL);
						  	gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(lbModeL),
						                      1,2,0,1,
						                      GTK_EXPAND,GTK_EXPAND,3,3);
						  	gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(lbSpeadL),
						                      2,3,0,1,
						                      GTK_EXPAND,GTK_EXPAND,3,3);

						  	  GtkWidget* lbFirstLayer = gtk_label_new("First Layer:");
						  	  GtkWidget* lbNextLayer = gtk_label_new("Next Layers:");
						  	  GtkWidget* lbLastLayer = gtk_label_new("Last Layer:");
						  	  gtk_widget_show(lbFirstLayer);gtk_widget_show(lbNextLayer);gtk_widget_show(lbLastLayer);

						      cmbFirstLayer = gtk_combo_box_new_text();
						      gtk_combo_box_set_title(GTK_COMBO_BOX(cmbFirstLayer),STR_ANIM_FIRST);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbFirstLayer),STR_ANIM_MODE_NONE);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbFirstLayer),STR_ANIM_MODE_COMBINE);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbFirstLayer),STR_ANIM_MODE_REPLACE);
						      gtk_widget_show(cmbFirstLayer);
						      gtk_combo_box_set_active(GTK_COMBO_BOX(cmbFirstLayer),0);
						      cmbNextLayer = gtk_combo_box_new_text();
						      gtk_combo_box_set_title(GTK_COMBO_BOX(cmbNextLayer),STR_ANIM_NEXT);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbNextLayer),STR_ANIM_MODE_NONE);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbNextLayer),STR_ANIM_MODE_COMBINE);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbNextLayer),STR_ANIM_MODE_REPLACE);
						      gtk_widget_show(cmbNextLayer);
						      gtk_combo_box_set_active(GTK_COMBO_BOX(cmbNextLayer),0);
						      cmbLastLayer = gtk_combo_box_new_text();
						      gtk_combo_box_set_title(GTK_COMBO_BOX(cmbLastLayer),STR_ANIM_LAST);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbLastLayer),STR_ANIM_MODE_NONE);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbLastLayer),STR_ANIM_MODE_COMBINE);
						      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbLastLayer),STR_ANIM_MODE_REPLACE);
						      gtk_widget_show(cmbLastLayer);
						      gtk_combo_box_set_active(GTK_COMBO_BOX(cmbLastLayer),0);

							   spbFirstLayer = gimp_spin_button_new(
							    						  		&adjFirstLayer,
							    						  		pl_vals.anim_fl,
							    						  		0, 10000,
							    						  		1, 1,
							    						  		1,
							    						  		10,
							    						  		0);
							   spbNextLayer = gimp_spin_button_new(
							    						  		&adjNextLayer,
							    						  		pl_vals.anim_nl,
							    						  		0, 10000,
							    						  		1, 1,
							    						  		1,
							    						  		10,
							    						  		0);
							   spbLastLayer = gimp_spin_button_new(
							    						  		&adjLastLayer,
							    						  		pl_vals.anim_ll,
							    						  		0, 10000,
							    						  		1, 1,
							    						  		1,
							    						  		10,
							    						  		0);
							   gtk_widget_show(spbFirstLayer);
							   gtk_widget_show(spbNextLayer);
							   gtk_widget_show(spbLastLayer);


						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(lbFirstLayer),
						                      0,1,1,2,
						                      GTK_EXPAND,GTK_EXPAND,3,3);
						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(cmbFirstLayer),
						                      1,2,1,2,
						                      GTK_EXPAND,GTK_EXPAND,3,3);
						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(spbFirstLayer),
						                      2,3,1,2,
						                      GTK_EXPAND,GTK_EXPAND,3,3);

						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(lbNextLayer),
						                      0,1,2,3,
						                      GTK_EXPAND,GTK_EXPAND,3,3);
						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(cmbNextLayer),
						                      1,2,2,3,
						                      GTK_EXPAND,GTK_EXPAND,3,3);
						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(spbNextLayer),
						                      2,3,2,3,
						                      GTK_EXPAND,GTK_EXPAND,3,3);

						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(lbLastLayer),
						                      0,1,3,4,
						                      GTK_EXPAND,GTK_EXPAND,3,3);
						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(cmbLastLayer),
						                      1,2,3,4,
						                      GTK_EXPAND,GTK_EXPAND,3,3);
						      gtk_table_attach(GTK_TABLE(tblAnimate),GTK_WIDGET(spbLastLayer),
						                      2,3,3,4,
						                      GTK_EXPAND,GTK_EXPAND,3,3);

						      g_signal_connect(GTK_COMBO_BOX(cmbFirstLayer), "changed",
						           G_CALLBACK (on_set_animate_type_combo),
						           GINT_TO_POINTER(gtk_combo_box_get_active(GTK_COMBO_BOX(cmbFirstLayer))));
						      g_signal_connect(GTK_COMBO_BOX(cmbNextLayer), "changed",
						      		G_CALLBACK (on_set_animate_type_combo),
						      		GINT_TO_POINTER(gtk_combo_box_get_active(GTK_COMBO_BOX(cmbNextLayer))));
						      g_signal_connect(GTK_COMBO_BOX(cmbLastLayer), "changed",
						      		G_CALLBACK (on_set_animate_type_combo),
						      		GINT_TO_POINTER(gtk_combo_box_get_active(GTK_COMBO_BOX(cmbLastLayer))));
							g_signal_connect(adjFirstLayer, "value_changed",
									G_CALLBACK (gimp_int_adjustment_update),
									   	&pl_vals.anim_fl);
							g_signal_connect(adjNextLayer, "value_changed",
									G_CALLBACK (gimp_int_adjustment_update),
									   	&pl_vals.anim_nl);
							g_signal_connect(adjLastLayer, "value_changed",
									G_CALLBACK (gimp_int_adjustment_update),
									   	&pl_vals.anim_ll);

	  //2.
      ///////////////////////////////////////////
	  //Add clone times frame:
		GtkWidget* frameCloneTimes = gtk_frame_new("");
 		gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameCloneTimes))),"<b>Clone Times:</b>");
 		gtk_widget_show(frameCloneTimes);
 		gtk_box_pack_start(GTK_BOX(main_vbox), frameCloneTimes, FALSE, TRUE, 0);
	  	//Add alingment for frame
	  	GtkWidget* alingmentFrameCloneTimes = gtk_alignment_new(
	  			  0.5,
	  			  0.5,
	  			  1,
	  			  1);
	  	gtk_alignment_set_padding(GTK_ALIGNMENT(alingmentFrameCloneTimes),0,0,6,3);
	  	gtk_widget_show(alingmentFrameCloneTimes);
	  	gtk_container_add(GTK_CONTAINER(frameCloneTimes), alingmentFrameCloneTimes);
	  		//Add table for frame:
	  	    GtkWidget* tblFrameCloneTimes = gtk_table_new(1,1,FALSE);
	  		gtk_widget_show(tblFrameCloneTimes);
	  		gtk_table_set_col_spacings(GTK_TABLE(tblFrameCloneTimes),6);
	  		gtk_container_add(GTK_CONTAINER(alingmentFrameCloneTimes), tblFrameCloneTimes);
			adjTimes = gimp_scale_entry_new(
				   				GTK_TABLE(tblFrameCloneTimes), //table
				   				0,			//column
				   				0,			//row
				   				"Repeat:",		//text
				   				120,			//minimum horizontal size of the GtkHScale.
				   				60,			//minimum horizontal size of the GtkSpinButton.
				   				pl_vals.times,//The initial value
				   				1,			//The lower boundary
				   				1000,			//The upper boundary
				   				1,			//The step increment
				   				1,			//The page increment (??)
				   				0,			//number of decimal digits
				   				TRUE,			//constrain (TRUE if the range of possible values of the GtkSpinButton should be the same as of the GtkHScale)
				   				0,			//spinbutton's lower boundary if constrain == FALSE
				   				0,			//spinbutton's upper boundary if constrain == FALSE
				   				"",	//A tooltip message for the scale and the spinbutton
				   				NULL //The widgets' help_id
				   		);
			g_signal_connect(adjTimes, "value_changed",
				   		G_CALLBACK (gimp_int_adjustment_update),
				   				       &pl_vals.times);
			//Add Expander for Additional Options
			GtkWidget* epAddOptions = gtk_expander_new(
					"<b>Additional Options</b>"
					);
			gtk_expander_set_use_markup(GTK_EXPANDER(epAddOptions), TRUE);
			gtk_widget_show(epAddOptions);
			gtk_box_pack_start(GTK_BOX(main_vbox), epAddOptions, FALSE, TRUE, 0);
			//Add alignment
			GtkWidget* alignmentAddOptions = gtk_alignment_new(
					0.5,
					0.5,
					1,
					1);
			gtk_alignment_set_padding(GTK_ALIGNMENT(alignmentAddOptions),0,0,3,3);
			gtk_widget_show(alignmentAddOptions);
			gtk_container_add(GTK_CONTAINER(epAddOptions), alignmentAddOptions);
			GtkWidget* addOptionsVBox = gtk_vbox_new (FALSE, 3);
			gtk_widget_show(addOptionsVBox);
			gtk_container_add(GTK_CONTAINER(alignmentAddOptions), addOptionsVBox);
			//Add general panel for select clone source:
			GtkWidget* frameAddOptions = gtk_frame_new ("");
			gtk_widget_show(frameAddOptions);
			gtk_box_pack_start(GTK_BOX(addOptionsVBox), frameAddOptions, FALSE, TRUE, 0);

			GtkWidget* tblAddOptions = gtk_table_new(2,2,FALSE);
			gtk_widget_show(tblAddOptions);
			gtk_container_add(GTK_CONTAINER(frameAddOptions), tblAddOptions);

			GtkWidget* lbInterpolation = gtk_label_new("Interpolation:");
			gtk_widget_show(lbInterpolation);
			gtk_table_attach(
					GTK_TABLE(tblAddOptions),
					lbInterpolation,
					0,1,
					0,1,
					GTK_SHRINK,
					GTK_EXPAND,
					3,3
					);
			sltInterpolation = gimp_int_combo_box_new(
					"None", 0,
					"Linear", 1,
					"Cubic", 2,
					"Sinc (Lanczos3)", 3,NULL);
			gtk_widget_show(GTK_WIDGET(sltInterpolation));
			gtk_table_attach(
					GTK_TABLE(tblAddOptions),
					GTK_WIDGET(sltInterpolation),
					1,2,
					0,1,
					GTK_EXPAND|GTK_FILL,
					GTK_EXPAND|GTK_FILL,
					3,3
					);

			  g_signal_connect(GTK_WIDGET(sltInterpolation),"changed",
			  				  			   G_CALLBACK (on_set_interpolation_radio),
			  				  			   	NULL);

      //Add the GtkFrame for Clone-Apply values:
      GtkWidget *frameApplyVals = gtk_frame_new ("");
      gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frameApplyVals))),
    		  "<b>Grouping of cloned layers:</b>");
      gtk_widget_show(frameApplyVals);
      gtk_box_pack_start(GTK_BOX(addOptionsVBox), frameApplyVals, FALSE, TRUE, 0);
      //Add to frameApplyVals a vbox for apply radios
      GtkWidget *vboxApply = gtk_vbox_new (FALSE, 3);
      gtk_widget_show(vboxApply);
      gtk_container_add(GTK_CONTAINER(frameApplyVals), vboxApply);
      //Add radios
      rbOneLayer = gtk_radio_button_new_with_label(NULL, "One layer (merge cloned layers)");
      listApplyRadios = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rbOneLayer));
      rbGroupLayer = gtk_radio_button_new_with_label(listApplyRadios, "Grouping cloned layers");
      listApplyRadios = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rbGroupLayer));
      rbEachLayer = gtk_radio_button_new_with_label(listApplyRadios, "Each clone to layer");
      listApplyRadios = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rbEachLayer));
      gtk_widget_show(rbOneLayer);
      gtk_widget_show(rbGroupLayer);
      gtk_widget_show(rbEachLayer);
      gtk_box_pack_start(GTK_BOX(vboxApply), rbOneLayer, FALSE, TRUE, 0);
      gtk_box_pack_start(GTK_BOX(vboxApply), rbGroupLayer, FALSE, TRUE, 0);
      gtk_box_pack_start(GTK_BOX(vboxApply), rbEachLayer, FALSE, TRUE, 0);
      g_signal_connect(rbOneLayer, "toggled",
      				  		G_CALLBACK (on_set_result_radio),
      				  		GINT_TO_POINTER((enum RESULT_LAYERS_TYPE)MERGE_LAYERS));
      g_signal_connect(rbGroupLayer, "toggled",
            				 G_CALLBACK (on_set_result_radio),
            				 GINT_TO_POINTER((enum RESULT_LAYERS_TYPE)GROUPING_LAYERS));
      g_signal_connect(rbEachLayer, "toggled",
            				  G_CALLBACK (on_set_result_radio),
            				  GINT_TO_POINTER((enum RESULT_LAYERS_TYPE)EACH_LAYERS));

      GtkWidget *hspResult = gtk_hseparator_new();
      gtk_widget_show(hspResult);
      gtk_box_pack_start(GTK_BOX(vboxApply), hspResult, FALSE, TRUE, 0);

      GtkWidget *tblGeneralVals = gtk_table_new(3,4,FALSE);
      gtk_widget_show(tblGeneralVals);
      gtk_box_pack_start(GTK_BOX(vboxApply), tblGeneralVals, FALSE, TRUE, 0);
      chkAutocrop = gtk_check_button_new_with_label("Autocrop layer");
      gtk_widget_show(chkAutocrop);
      g_signal_connect(chkAutocrop, "toggled",
                  				 G_CALLBACK (on_set_autocrop_radio),
                  				 NULL);
      gtk_table_attach(
      					GTK_TABLE(tblGeneralVals),
      					GTK_WIDGET(chkAutocrop),
      					0,1,
      					0,1,
      					GTK_EXPAND,
      					GTK_EXPAND,
      					3,3
      					);

      GtkWidget *lbOrderLayer = gtk_label_new ("Order:");
      gtk_widget_show(lbOrderLayer);
      gtk_table_attach(
      					GTK_TABLE(tblGeneralVals),
      					GTK_WIDGET(lbOrderLayer),
      					1,2,
      					0,1,
      					GTK_EXPAND,
      					GTK_EXPAND,
      					3,3
      					);

      GSList *listOrderLayerRadios = NULL;
      rbOrderLayerUp = gtk_radio_button_new_with_label(NULL, "UP");
      listApplyRadios = gtk_radio_button_get_group (GTK_RADIO_BUTTON(rbOrderLayerUp));
      rbOrderLayerDown = gtk_radio_button_new_with_label(listApplyRadios, "DOWN");
      gtk_widget_show(rbOrderLayerUp);
      gtk_widget_show(rbOrderLayerDown);
      gtk_table_attach(
      					GTK_TABLE(tblGeneralVals),
      					GTK_WIDGET(rbOrderLayerUp),
      					2,3,
      					0,1,
      					GTK_EXPAND,
      					GTK_EXPAND,
      					3,3
      					);
      gtk_table_attach(
      					GTK_TABLE(tblGeneralVals),
      					GTK_WIDGET(rbOrderLayerDown),
      					3,4,
      					0,1,
      					GTK_EXPAND,
      					GTK_EXPAND,
      					3,3
      					);

      g_signal_connect(rbOrderLayerUp, "toggled",
                  				  G_CALLBACK (on_set_order_radio),
                  				  GINT_TO_POINTER(UP_DOWN_ORDER));
      g_signal_connect(rbOrderLayerDown, "toggled",
                        				  G_CALLBACK (on_set_order_radio),
                        				  GINT_TO_POINTER(DOWN_UP_ORDER));



      GtkWidget *hspBottom01 = gtk_hseparator_new();
      gtk_widget_show(hspBottom01);
      gtk_table_attach(
            					GTK_TABLE(tblGeneralVals),
            					GTK_WIDGET(hspBottom01),
            					0,4,
            					1,2,
            					GTK_EXPAND|GTK_FILL,
            					GTK_EXPAND|GTK_FILL,
            					3,3
            					);

      chkAddBackGround =gtk_check_button_new_with_label("add backgroung");
      gtk_widget_show(chkAddBackGround);
      gtk_table_attach(
                  					GTK_TABLE(tblGeneralVals),
                  					GTK_WIDGET(chkAddBackGround),
                  					0,2,
                  					2,3,
                  					GTK_EXPAND|GTK_FILL,
                  					GTK_EXPAND|GTK_FILL,
                  					3,3
                  					);
      g_signal_connect(chkAddBackGround, "toggled",
                        				  G_CALLBACK (on_set_add_bg_radio),
                        				  NULL);

      cmbBGType = gtk_combo_box_new_text();
      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbBGType),STR_BG_FILL);
      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbBGType),STR_FG_FILL);
      gtk_combo_box_append_text(GTK_COMBO_BOX(cmbBGType),STR_VIEW_FILL);
      gtk_widget_show(cmbBGType);
      gtk_table_attach(
                        					GTK_TABLE(tblGeneralVals),
                        					GTK_WIDGET(cmbBGType),
                        					2,4,
                        					2,3,
                        					GTK_EXPAND|GTK_FILL,
                        					GTK_EXPAND|GTK_FILL,
                        					3,3
                        					);

      gtk_combo_box_set_active(GTK_COMBO_BOX(cmbBGType),0);

      g_signal_connect(cmbBGType, "changed",
                              G_CALLBACK (on_set_add_bg_combo),
                              				 NULL);


  ///////////////////////////////////////

  //3.
  //Add hseparator
  GtkWidget *hspBottom = gtk_hseparator_new();
  gtk_widget_show(hspBottom);
  gtk_box_pack_end(GTK_BOX(main_vbox), hspBottom, FALSE, TRUE, 0);
 //Add hbox for cust.buttons
  GtkWidget *hboxForButtons = gtk_hbox_new(FALSE,3);
  gtk_widget_show(hboxForButtons);
  gtk_box_pack_end(GTK_BOX(main_vbox), hboxForButtons, FALSE, TRUE, 0);
  //Add cust.buttons to hboxForButtons
  imgResetVals = gtk_image_new_from_stock (GIMP_STOCK_RESET, GTK_ICON_SIZE_BUTTON);
  btResetVals = gtk_button_new_with_label("Reset All");
  gtk_button_set_image (GTK_BUTTON(btResetVals), imgResetVals);
  gtk_button_set_use_stock(GTK_BUTTON(btResetVals),TRUE);

  GtkWidget *btUndo = gtk_button_new_with_label("Undo");
  GtkWidget *imgUndo = gtk_image_new_from_stock (GTK_STOCK_UNDO, GTK_ICON_SIZE_BUTTON);
  gtk_button_set_image (GTK_BUTTON (btUndo), imgUndo);

  GtkWidget *btClone = gtk_button_new_with_label("Clone");
  GtkWidget *imgClone = gtk_image_new_from_stock (GTK_STOCK_YES, GTK_ICON_SIZE_BUTTON);
  gtk_button_set_image (GTK_BUTTON (btClone), imgClone);

  gtk_widget_show(btResetVals);
  gtk_widget_show(imgResetVals);

  gtk_widget_show(btUndo);
  gtk_widget_show(imgUndo);

  gtk_widget_show(btClone);
  gtk_widget_show(imgClone);

  progressBar = gtk_progress_bar_new();
  gtk_widget_show(progressBar);
  gtk_box_pack_start(GTK_BOX(hboxForButtons),progressBar, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(hboxForButtons), btResetVals, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hboxForButtons), btUndo, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hboxForButtons), btClone, FALSE, TRUE, 0);

  g_signal_connect(btUndo,"clicked",G_CALLBACK(onUndoClick),NULL);
  g_signal_connect(btResetVals,"clicked",G_CALLBACK(onResetVals),NULL);
  g_signal_connect(btClone,"clicked",G_CALLBACK(onCloneClick),NULL);


  //Add hseparator
  GtkWidget *hspTop = gtk_hseparator_new();
  gtk_widget_show(hspTop);
  gtk_box_pack_start(GTK_BOX(main_vbox), hspTop, FALSE, TRUE, 0);

//Setup dialog's widgets:
  initDialogVals();

  //Show gimp-dialog window:
  gtk_widget_show (dialog);

  run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);

  gtk_widget_destroy (dialog);

  return run;
}
