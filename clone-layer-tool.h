/* clone-layer tool - plugin for GIMP
 *
 * clone-layer-tool.h
 *
 *  Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 *
 */

#ifndef CLONE_LAYER_TOOL_H_
#define CLONE_LAYER_TOOL_H_

#include <math.h>
#include <stdlib.h>

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include <libgimpmath/gimpmath.h>
#include <libgimpbase/gimpbaseenums.h>

/****************************************************
 **************** Defines **************************
****************************************************/
#define PLUG_IN_PROC   "plug-in-clone-layer-tool"
#define PLUG_IN_BINARY "clone-layer-tool"
#define PLUG_IN_ROLE   "gimp-clone-layer-tool"

const gchar *STR_ANIM_MODE_COMBINE = "combine";
const gchar *STR_ANIM_MODE_REPLACE = "replace";
const gchar *STR_ANIM_MODE_NONE = "none";

/*************************************************
 *************** Typedefs ************************
 *************************************************/
enum TYPE_ROTATE_COORDINATES {
	FIXED = 0,
	DINAMIC
};


enum CLONE_LAYER {
	FIRST=0,
	LAST
};

typedef enum {
	UP_DOWN_ORDER = 0,
	DOWN_UP_ORDER = 1
}LayerOrderType;

enum AUTO_COORD_TYPE {
	TOP_LEFT = 0,
	TOP_RIGHT,
	CENTER_CENTER,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};

enum RESULT_LAYERS_TYPE {
	MERGE_LAYERS = 0,
	GROUPING_LAYERS,
	EACH_LAYERS
};

typedef enum {
	CHK_MAX_ANGLE,
	CHK_MIN_ANGLE,

	CHK_MIN_STEP_X,
	CHK_MAX_STEP_X,
	CHK_MIN_STEP_Y,
	CHK_MAX_STEP_Y,

	CHK_MIN_STEP_W,
	CHK_MAX_STEP_W,
	CHK_MIN_STEP_H,
	CHK_MAX_STEP_H,

	CHK_MIN_ALPHA,
	CHK_MAX_ALPHA,

	CHK_SET_W,
	CHK_SET_H,

	CHK_ANGLE,

	CHK_STEP_X,
	CHK_STEP_Y,

	CHK_OPACITY,

	CHK_BLUR,

	CHK_MIN_BLUR,
	CHK_MAX_BLUR,

	CHK_SPREAD,
	CHK_MIN_SPREAD,
	CHK_MAX_SPREAD,

	CHK_COLORIZE,
	CHK_MIN_HUE,
	CHK_MAX_HUE,
	CHK_COLORIZE_SAT,
	CHK_COLORIZE_LIGHT

} ChkValues;

typedef enum {
	ADD_BG_BG = 0,
	ADD_BG_FG = 1,
	ADD_BG_VIEW =2
}AddBGType;

//
typedef struct
{
  gint     angle;
  gint     times;
  gint     pX;
  gint     pY;
  gint     step_x;
  gint     step_y;
  gint     random_angle_from;
  gint     random_angle_to;
  gint     ran_step_x_min;
  gint     ran_step_x_max;
  gint     ran_step_y_min;
  gint     ran_step_y_max;
  gint     step_width;
  gint     step_height;
  gint     ran_step_width_min;
  gint     ran_step_width_max;
  gint     ran_step_height_min;
  gint     ran_step_height_max;
  gboolean keep_aspect;
  gint     opacity;
  gint     ran_step_opacity_min;
  gint     ran_step_opacity_max;
  gint	   random_blur_min;
  gint 	   random_blur_max;
  enum CLONE_LAYER clone_type;
  enum RESULT_LAYERS_TYPE result_layes;
  enum AUTO_COORD_TYPE resize_type;
  enum AUTO_COORD_TYPE start_corner_type;
  enum AUTO_COORD_TYPE end_corner_type;
  enum TYPE_ROTATE_COORDINATES rotate_coord_type;
  enum AUTO_COORD_TYPE rotate_corner_type;
  gboolean is_autocrop;
  GimpInterpolationType interpolation;
  gboolean add_bg;
  AddBGType add_bg_type;
  gdouble blur_radius;
  LayerOrderType layer_order;
  //shadow:
  gint shadow_size;
  gint shadow_angle;
  gint shadow_distance;
  gint shadow_opacity;
  gint shadow_spread;
  GimpRGB shadow_color;
  //Spread
  gint spread_radius;
  gint random_spread_min;
  gint random_spread_max;
  //Colorize
  gint colorize_hue;
  gint random_hue_min;
  gint random_hue_max;
  gint colorize_sat;
  gint colorize_light;
  //Animation
  gint anim_fl;
  gint anim_nl;
  gint anim_ll;
  gint anim_tf;
  gint anim_tn;
  gint anim_tl;
  gboolean animate_enable;
} MyCloneVals;

//layer data
typedef struct{
	gint x1;
	gint y1;
	gint x2;
	gint y2;
	gint w;
	gint h;
	gint opacity;
}LayerData;

//addition info about layer data:
typedef struct{
	gint32 id;
	gint margin_top;
	gint margin_bottom;
	gint margin_left;
	gint margin_right;
}LayerStack;

GRand  *grnd;

/*************************************************
 ************* Prototypes ************************
 *************************************************/
static void query       (void);

static void run         (const gchar      *name,
                         gint              nparams,
                         const GimpParam  *param,
                         gint             *nreturn_vals,
                         GimpParam       **return_vals);

static gboolean createWorkLayer(GimpDrawable *drawable);

static gint getRandomRange(gint nFrom, gint nTo);

static  LayerData getLayerData(gint32 layer);

static void autocropLayer(gint32 layer, gboolean fromBG);

static gint32 cloneLayer(gint32 layer);

static void moveLayer(gint32 layer, gint sX, gint sY, gint sN, gint rType);
static void rotateLayer(gint32 layer, gdouble angle, gint sN, gint rType);
static void resizeLayer(gint32 layer, gint rWidth, gint rHeight,gint sN, gint rType);
static void opacityLayer(gint32 layer, gdouble opacity);
static void blurLayer(gint32 layer, gdouble radius, gint sN, gint rType);
static void dropShadow(gint32 layer, gint32 angle, gint32 size, gint32 distance, GimpRGB color, gint32 opacity,gint sN);
static void colorizeLayer(gint32 layer, gint hue, gint sat, gint light, gint sN, gint rType);
static void spreadLayer(gint32 layer,  gdouble radius, gint sN, gint rType);

static void onUndoClick();
void onCloneClick();
static void onSuccess();
static void onExit(GimpRunMode run_mode);

static void initVals();

void add_under_layer(gint32 srclayer, gint32 dstlayer);
void draw_blurshape(gint layer, gint size, gint initgrowth, gint32 sel, gboolean invert);

static MyCloneVals pl_vals;

static LayerData layerData = {
		0,0,
		1,1,
		1,1
};

static gint32 workLayer = -1;

static GimpDrawable *curDrawable = NULL;

static gint32 curImage = -1;

static gint32 groupLayer = -1;

GList *clonedLayersList=NULL;

void freeLayerStack(GList *stack);
LayerStack *findLayerStack(gint32 id);

GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  NULL,
  query,
  run
};


#endif /* CLONE_LAYER_TOOL_H_ */
