/* clone-layer tool - plugin for GIMP * /

/*
 * dialog.h
 *
 *  Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

#ifndef DIALOG_H_
#define DIALOG_H_


#include <libgimp/gimpui.h>
#include <string.h>
//add to .c!
/*
#include <libgimp/gimp.h>
#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gtk/gtkwidget.h>
#include <gtk-2.0/gtk/gtkradiobutton.h>
#include <gtk-2.0/gtk/gtktable.h>
#include <gtk-2.0/gtk/gtkcheckbutton.h>
#include <gtk-2.0/gtk/gtktogglebutton.h>
#include <gtk-2.0/gtk/gtkcombobox.h>
#include <gtk-2.0/gtk/gtklabel.h>
*/
#include "clone-layer-tool.h"

#include "onUndoClick.c"

const gchar *STR_BG_FILL = "BG-Color";
const gchar *STR_FG_FILL = "FG-Color";
const gchar *STR_VIEW_FILL = "Visible";



const gchar *STR_ANIM_FIRST = "First";
const gchar *STR_ANIM_NEXT = "Next";
const gchar *STR_ANIM_LAST = "Last";


void on_set_radio(GtkToggleButton *togglebutton, gpointer clone_type);
void on_set_auto_coord_radio(GtkToggleButton *togglebutton, gpointer coord_type);
void on_set_resize_type_radio(GtkToggleButton *togglebutton, gpointer coord_type);
void on_set_start_corner_radio(GtkToggleButton *togglebutton, gpointer corner_type);
void on_set_rotate_coord_radio(GtkToggleButton *togglebutton, gpointer coord_type);
void checkValues(GtkToggleButton *togglebutton, gpointer whatCheck);
void on_size_changed(GtkToggleButton *togglebutton, gpointer whatCheck);
void on_set_aspect_ratio(GtkToggleButton *togglebutton, gpointer none);
void on_set_autocrop_radio(GtkToggleButton *togglebutton, gpointer yes);
void on_set_interpolation_radio(GimpIntComboBox *combo_box, gpointer none);
void on_set_add_bg_radio(GtkToggleButton *togglebutton, gpointer checked);
void on_set_add_bg_combo(GtkComboBox *combobox, gpointer none);
void on_set_animate_on_radio(GtkToggleButton *togglebutton, gpointer none);
void on_set_animate_type_combo(GtkComboBox *combo_box, gpointer type);
gboolean clone_dialog(void);
void onResetVals();

// Widgets:
GtkWidget
	*frameAnimate,
	*spbManRotateCoordX,
	*spbManRotateCoordY,
	*lbResizeType,
	*chkAutocrop,
	*spbRanStepHeightMax,
	*spbRanStepHeightMin,
	*lbStartCorners,
	*lbEndCorners,
	*rbRotateTopLeft,
	*rbRotateTopRight,
	*rbRotateBottomLeft,
	*rbRotateBottomRight,
	*rbRotateCenter,
	*rbRotateFixed,
	*rbRotateDinamically,
	*rbCornerTopLeft,
	*rbCornerTopRight,
	*rbCornerCenter,
	*rbCornerBottomLeft,
	*rbCornerBottomRight,
	*rbEndCornerTopLeft,
	*rbEndCornerTopRight,
	*rbEndCornerCenter,
	*rbEndCornerBottomLeft,
	*rbEndCornerBottomRight,
	*rbResizeTopLeft,
	*rbResizeTopRight,
	*rbResizeCenter,
	*rbResizeBottomLeft,
	*rbResizeBottomRight,
	*chkAspectRatio,
	*rbOneLayer,
	*rbGroupLayer,
	*rbEachLayer,
	*spbRanStepXMin,
	*spbRanStepXMax,
	*spbRanStepYMin,
	*spbRanStepYMax,
	*spbRanStepWidthMin,
	*spbRanStepWidthMax,
	*spbRanStepAlphaMin,
	*spbRanStepAlphaMax,
	*spbRanBlurMin,
	*spbRanBlurMax,
	*rbOrderLayerUp,
	*rbOrderLayerDown,
	*cmbBGType,
	*chkAddBackGround,
	//shadow:
	*btShadowColor,
	//Spread
	*spbRanSpreadMin,
	*spbRanSpreadMax,
	//Colorize
	*spbRanHueMin,
	*spbRanHueMax,
	//Animation
	*cmbFirstLayer,
	*cmbNextLayer,
	*cmbLastLayer,

	*spbFirstLayer,
	*spbNextLayer,
	*spbLastLayer,
	//Animate
	*chkEnableAnimate
	;

GtkWidget *imgResetVals, *btResetVals;

GimpIntComboBox* sltInterpolation;

GtkWidget *progressBar;

GtkObject
	*adjAngle,
	*adjTimes,
	*adjStepX,
	*adjStepY,
	*adjRandomAngleFrom,
	*adjRandomAngleTo,
	*adjManRotateCoordX,
	*adjManRotateCoordY,
	*adjRanStepXMin,
	*adjRanStepXMax,
	*adjRanStepYMin,
	*adjRanStepYMax,
	*adjStepWidth,
	*adjStepHeight,
	*adjRanStepWidthMin,
	*adjRanStepWidthMax,
	*adjRanStepHeightMin,
	*adjRanStepHeightMax,
	*adjAlphaStep,
	*adjRanStepAlphaMin,
	*adjRanStepAlphaMax,
	*adjBlurRadius,
	*adjRanBlurMin,
	*adjRanBlurMax,
	*adjShadowSize,
	*adjShadowAngle,
	*adjShadowDistance,
	*adjShadowOpacity,
	*adjSpreadSize,
	*adjRanSpreadMin,
	*adjRanSpreadMax,
	*adjColorizeHue,
	*adjRanHueMin,
	*adjRanHueMax,
	*adjColorizeSat,
	*adjColorizeLight,
	*adjFirstLayer,
	*adjNextLayer,
	*adjLastLayer
	;

#endif /* DIALOG_H_ */
