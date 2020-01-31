/* clone-layer tool - plugin for GIMP


 * Clone-Layer Tool - 0.1
 *
 * Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

//TODO:
//add gimp-colorize
//add plug-in-spread

#include "clone-layer-tool.h"
#include "run.c"
#include "onExit.c"
#include "onSuccess.c"
#include "onCloneClick.c"

static gchar *l_blure_proc = "plug-in-gauss";

//Run main
MAIN()

/****************************************************
 * *****************Functions **********************
 * ************************************************/

static void query (void)
{
  static GimpParamDef args[] =
  {
	//
    {GIMP_PDB_INT32,"run-mode","Run mode{RUN-INTERACTIVE (0), RUN-NONINTERACTIVE - disable!}"}, //param[0]
    {GIMP_PDB_IMAGE,"image","Input image"}, //param[1]
    {GIMP_PDB_DRAWABLE,"drawable","Input drawable"} //param[2]
  };
//
  gimp_install_procedure(
	PLUG_IN_PROC,
    "Clone layers Tool - v0.1",
    "Clone layer x-times and move/scale or rotate it",
    "Remy AWM",
    "Copyright Remy AWM",
    "2011",
    "_Clone-Layer Tool...",
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register(PLUG_IN_PROC,
                             "<Image>/Layer");
}

static void initVals(){
	pl_vals.angle = 0;
	pl_vals.times =	3;
	pl_vals.pX =0;
	pl_vals.pY =0;
	pl_vals.step_x = 0;
	pl_vals.step_y = 0;
	pl_vals.random_angle_from = 0;
	pl_vals.random_angle_to = 0;
	pl_vals.ran_step_x_min =0;
	pl_vals.ran_step_x_max =0;
	pl_vals.ran_step_y_min =0;
	pl_vals.ran_step_y_max =0;
	pl_vals.step_width =0;
	pl_vals.step_height =0;
	pl_vals.ran_step_width_min=0;
	pl_vals.ran_step_width_max=0;
	pl_vals.ran_step_height_min=0;
	pl_vals.ran_step_height_max=0;
	pl_vals.keep_aspect=TRUE;
	pl_vals.opacity=0;
	pl_vals.ran_step_opacity_min=0;
	pl_vals.ran_step_opacity_max=0;
	pl_vals.random_blur_min=0;
	pl_vals.random_blur_max=0;
	pl_vals.clone_type =LAST;
	pl_vals.result_layes =GROUPING_LAYERS;
	pl_vals.resize_type =CENTER_CENTER;
	pl_vals.start_corner_type=TOP_RIGHT;
	pl_vals.end_corner_type=TOP_LEFT;
	pl_vals.rotate_coord_type=FIXED;
	pl_vals.rotate_corner_type=CENTER_CENTER;
	pl_vals.is_autocrop=TRUE;
	pl_vals.interpolation=GIMP_INTERPOLATION_CUBIC;
	pl_vals.blur_radius = (gdouble)0;
	pl_vals.layer_order = UP_DOWN_ORDER;
	pl_vals.add_bg = FALSE;
	pl_vals.add_bg_type = ADD_BG_BG;
	//shadow:
	pl_vals.shadow_size = 0;
	pl_vals.shadow_angle = 120;
	pl_vals.shadow_distance = 0;
	pl_vals.shadow_opacity = 75;
	gimp_rgb_set(&pl_vals.shadow_color, 0,0,0);
	//Spread
	pl_vals.spread_radius = 0;
	pl_vals.random_spread_min = 0;
	pl_vals.random_spread_max = 0;
	//Colorize
	pl_vals.colorize_hue = 0;
	pl_vals.random_hue_min = 0;
	pl_vals.random_hue_max = 0;
	pl_vals.colorize_sat = 50;
	pl_vals.colorize_light = 0;
	//Aimation
	pl_vals.animate_enable = FALSE;
	pl_vals.anim_fl = 100;
	pl_vals.anim_nl = 100;
	pl_vals.anim_ll = 100;
	pl_vals.anim_tf = 0;
	pl_vals.anim_tn = 0;
	pl_vals.anim_tl = 0;
}

void freeLayerStack(GList *stack){
	GList *l;
	for(l = g_list_last(stack); l; l = l->prev)
		g_free(l->data);
}
LayerStack *findLayerStack(gint32 id){
	LayerStack *rl;
	GList *l;
	for(l = g_list_last(clonedLayersList); l; l = l->prev){
		rl= l->data;
		if(id == rl->id)
			return rl;
	}
	return NULL;
}
//
static gboolean createWorkLayer(GimpDrawable *drawable){
	gboolean res = TRUE;

	if(workLayer!=-1){
		if(gimp_item_is_valid(workLayer))
			gimp_image_remove_layer(curImage,workLayer);
		workLayer=-1;
	}

	if(gimp_item_is_valid(drawable->drawable_id))
		workLayer = gimp_layer_copy(drawable->drawable_id);

  if(workLayer == -1)
	  res = FALSE;
  else{
	  if(!gimp_image_insert_layer(curImage,workLayer,0,-1))
		  res = FALSE;
	  else{
		  gchar *lName = gimp_item_get_name(drawable->drawable_id);
		  gchar newName[256]="";
		  sprintf(newName,"%s-clt",lName);
		  gimp_item_set_name(workLayer, newName);
		  //Обрезаем слой
		  gimp_layer_resize_to_image_size(workLayer);
		  autocropLayer(workLayer, TRUE);
		  //Получаем коорд. и размеры слоя:
		  layerData = getLayerData(workLayer);
	  }
  }
  return res;
  }
//
static gint getRandomRange(gint nFrom, gint nTo){
	//gint rN = rand() % (nFrom-nTo)+1 + nFrom;
	gint rN = g_rand_int_range(grnd, nFrom, nTo);
	return rN;
}
//
static  LayerData getLayerData(gint32 layer){
	LayerData tmpData;

	gimp_drawable_offsets(layer, &tmpData.x1, &tmpData.y1);
	tmpData.w =  gimp_drawable_width(layer);
	tmpData.h = gimp_drawable_height(layer);
	tmpData.x2 = tmpData.x1+tmpData.w;
	tmpData.y2 = tmpData.y1+tmpData.h;
	tmpData.opacity = gimp_layer_get_opacity(layer);

	return tmpData;
}
//
static void autocropLayer(gint32 layer, gboolean fromBG){
	if(fromBG){
	//Try autocrop from backgrd with plug-in-autocrop-layer()
	GimpParam    *return_vals;
	gint          nreturn_vals;
	//plug-in-autocrop-layer
	 return_vals = gimp_run_procedure ("plug-in-autocrop-layer",
		                                             &nreturn_vals,
		                                             GIMP_PDB_INT32, GIMP_RUN_NONINTERACTIVE,
		                                             GIMP_PDB_IMAGE, curImage,
		                                             GIMP_PDB_DRAWABLE, layer,
		                                             GIMP_PDB_END);
	 if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS){
		          gimp_progress_end();
	               return;
	             }
	  g_printf("Error on call gimp_run_procedure(%s)","plug-in-autocrop-layer");
	}

		gimp_layer_resize_to_image_size(layer);
		//Autocrop layer
		//make select from alpha

		gimp_image_select_item(
				curImage,
				GIMP_CHANNEL_OP_REPLACE,
				layer
				);
		//Get select coord.:
		gint x1, x2, y1, y2;
		gboolean non_empty = TRUE;
		gimp_selection_bounds(
				curImage,
				&non_empty,
				&x1,
				&y1,
				&x2,
				&y2
				);
		gimp_selection_none(curImage);

		gimp_layer_resize(layer,
				x2-x1,
				y2-y1,
				x1*(-1), y1*(-1));
}

//Return layerId on success or -1 if not
static gint32 cloneLayer(gint32 layer){
	gint32 newLayerId = gimp_layer_copy(layer);
	gint llist = g_list_length(clonedLayersList);

	  gchar *lName = gimp_item_get_name(workLayer);

	  gchar newName[256]="";
	  sprintf(newName,"%s #%i",lName, llist);
	  gimp_item_set_name(newLayerId, newName);

	gboolean res = FALSE;

	gint lastPos = -1;

	if(pl_vals.layer_order == DOWN_UP_ORDER){
		if(layer == workLayer)
			lastPos = gimp_image_get_layer_position(curImage,curDrawable->drawable_id);
		else
			lastPos = gimp_image_get_layer_position(curImage,layer);
	}

	res = gimp_image_insert_layer(curImage,newLayerId,0,lastPos);

	LayerStack *itemLayer = g_new(LayerStack,1);
	itemLayer->id = newLayerId;
	itemLayer->margin_bottom = 0;
	itemLayer->margin_top = 0;
	itemLayer->margin_left = 0;
	itemLayer->margin_right = 0;

	clonedLayersList = g_list_append(
			clonedLayersList,
			itemLayer
			);

	return res?newLayerId:-1;
}
//
static void opacityLayer(gint32 layer, gdouble opacity){
	if(opacity==0) return;

	gdouble newOpacity =opacity;

	if(newOpacity>(gdouble)100) newOpacity = (gdouble)100;
	if(newOpacity<(gdouble)0) newOpacity = (gdouble)0;

	 gimp_layer_set_opacity(layer,newOpacity);
}
//
static void blurLayer(gint32 layer, gdouble radius, gint sN, gint rType){
	 GimpParam    *return_vals;
	 gint          nreturn_vals;
	 float  l_hor_radius = rType==1?radius:(radius*(sN+1));
	 float  l_ver_radius = l_hor_radius;

    if(l_hor_radius==0) return;

    LayerData tmpCurLayer = getLayerData(layer);
    gdouble ramt = radius*2;
	 gimp_layer_resize(layer,tmpCurLayer.w+ramt, tmpCurLayer.h+ramt, ramt/2, ramt/2);
	 return_vals = gimp_run_procedure (l_blure_proc,
		                                             &nreturn_vals,
		                                             GIMP_PDB_INT32, GIMP_RUN_NONINTERACTIVE,
		                                             GIMP_PDB_IMAGE, curImage,
		                                             GIMP_PDB_DRAWABLE, layer,
		                                             GIMP_PDB_FLOAT, l_hor_radius,
		                                             GIMP_PDB_FLOAT, l_ver_radius,
		                                             GIMP_PDB_INT32, 0, /* Blur method { IIR (0), RLE (1) } */
		                                             GIMP_PDB_END);

	 if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS){
		          gimp_progress_end();

	             }
	 else
		 g_printf("Error on call gimp_run_procedure(%s)",l_blure_proc);
	 //autocropLayer(layer,TRUE);
	 return;
}
//
static void moveLayer(gint32 layer, gint sX, gint sY, gint sN, gint rType){
	if(sX==0 && sY==0) return;

	GList *l = NULL;
	gint32  prevLayer = -1;
	if(l = g_list_last(clonedLayersList)->prev){
		LayerStack *ils=l->data;
		prevLayer = ils->id;
	}

	LayerData tmpCurLayer = getLayerData(layer);
	LayerData tmpPrevLayer = getLayerData(prevLayer==-1?workLayer:prevLayer);
	//??? maybe.. but seems it wrong...
	//LayerData tmpWorkLayer = getLayerData(workLayer);
	//seems it work right
	LayerData tmpWorkLayer = tmpCurLayer;

	//test:
	gint w_margin_left=0;
	gint w_margin_top=0;
	gint w_margin_right=0;
	gint w_margin_bottom=0;

	gint p_margin_left=0;
	gint p_margin_top=0;
	gint p_margin_right=0;
	gint p_margin_bottom=0;

	LayerStack *layerWorkItem = findLayerStack(layer);
	if(layerWorkItem!=NULL){
	 w_margin_left=layerWorkItem->margin_left;
	 w_margin_top=layerWorkItem->margin_top;
	 w_margin_right=layerWorkItem->margin_right;
	 w_margin_bottom=layerWorkItem->margin_bottom;}

	LayerStack *layerPrevItem = findLayerStack(prevLayer==-1?workLayer:prevLayer);
	if(layerPrevItem!=NULL){
		 p_margin_left=layerPrevItem->margin_left;
		 p_margin_top=layerPrevItem->margin_top;
		 p_margin_right=layerPrevItem->margin_right;
		 p_margin_bottom=layerPrevItem->margin_bottom;}


	gint startX, endX, startY, endY, offX, offY;

	if(pl_vals.start_corner_type == TOP_LEFT){ //!
		startX = tmpWorkLayer.x1+w_margin_left;
		startY = tmpWorkLayer.y1+w_margin_top;
		endX = tmpPrevLayer.x1+p_margin_left;
		endY = tmpPrevLayer.y1+p_margin_top;
	}
	else if(pl_vals.start_corner_type == TOP_RIGHT){ //!
		startX = tmpWorkLayer.x1+w_margin_left;
		startY = tmpWorkLayer.y1+w_margin_top;
		endX = tmpPrevLayer.x2-p_margin_right;
		endY = tmpPrevLayer.y1+p_margin_top;
	}

	else if(pl_vals.start_corner_type == BOTTOM_LEFT){
		startX = tmpWorkLayer.x1+w_margin_left;
		startY = tmpWorkLayer.y1+w_margin_top;
		endX = tmpPrevLayer.x1+p_margin_right;
		endY = tmpPrevLayer.y2-p_margin_bottom;
	}
	else if(pl_vals.start_corner_type == BOTTOM_RIGHT){
		startX = tmpWorkLayer.x1+w_margin_left;
		startY = tmpWorkLayer.y1+w_margin_top;
		endX = tmpPrevLayer.x2-p_margin_right;
		endY = tmpPrevLayer.y2-p_margin_bottom;
	}
	else{
		startX = tmpWorkLayer.x1+w_margin_left;
		startY = tmpWorkLayer.y1+w_margin_top;

		endX = tmpPrevLayer.x1+p_margin_left+((tmpPrevLayer.w-(p_margin_left+p_margin_right))/2);
		endY = tmpPrevLayer.y1+p_margin_top+((tmpPrevLayer.h-(p_margin_bottom+p_margin_top))/2);
	}


	if(pl_vals.end_corner_type == TOP_LEFT){
		offX =endX-startX;
		offY =endY-startY;
	}
	else if(pl_vals.end_corner_type == TOP_RIGHT){
		offX=(endX-startX)-tmpCurLayer.w+(w_margin_right+w_margin_left);
		offY =endY-startY;
	}
	else if(pl_vals.end_corner_type == BOTTOM_LEFT){
		offX=endX-startX;
		offY =endY-startY-tmpCurLayer.h+(w_margin_bottom+w_margin_top);
	}
	else if(pl_vals.end_corner_type == BOTTOM_RIGHT){
		offX = (endX-startX)-tmpCurLayer.w+(w_margin_right+w_margin_left);
		offY = (endY-startY)-tmpCurLayer.h+(w_margin_bottom+w_margin_top);
	}
	else{
		offX = (endX-startX)-((tmpCurLayer.w-(w_margin_left+w_margin_right))/2);
		offY = (endY-startY)-((tmpCurLayer.h-(w_margin_bottom+w_margin_top))/2);
	}


	gint _x = sX==0?0:((offX)+sX);
	gint _y = sY==0?0:((offY)+sY);

	gimp_layer_translate(layer, _x, _y);
}
//
static void resizeLayer(gint32 layer, gint rWidth, gint rHeight, gint sN, gint rType){
	if(rWidth==0 && rHeight==0) return;

	LayerData tmpLayerData = getLayerData(layer);
	LayerData tmpWorkLayerData = getLayerData(workLayer);
	gdouble curAspect = (gdouble)tmpWorkLayerData.w/(gdouble)tmpWorkLayerData.h;

	gint _w = (rWidth*(sN+1));
	gint _h = (rHeight*(sN+1));

	// random:
	if(rType==1 || rType==3)
		_w = rWidth;

	if(rType==2 || rType==3)
		_h = rHeight;

	//keep aspect
	if(pl_vals.keep_aspect){
		_h = (gdouble)_w/curAspect;
	}

	gdouble _x1, _y1, _x2, _y2;

	if(pl_vals.resize_type == TOP_LEFT){
		_x1 = (gdouble)tmpLayerData.x1;
		_y1 = (gdouble)tmpLayerData.y1;
		_x2 = (gdouble)(tmpLayerData.x2+_w);
		_y2 = (gdouble)(tmpLayerData.y2+_h);
	}
	else if(pl_vals.resize_type == TOP_RIGHT){
		_x1 = (gdouble)(tmpLayerData.x1-_w);
		_y1 = (gdouble)tmpLayerData.y1;
		_x2 = (gdouble)tmpLayerData.x2;
		_y2 = (gdouble)(tmpLayerData.y2+_h);
	}

	else if(pl_vals.resize_type == BOTTOM_LEFT){
		_x1 = (gdouble)tmpLayerData.x1;
		_y1 = (gdouble)(tmpLayerData.y1-_h);
		_x2 = (gdouble)(tmpLayerData.x2+_w);
		_y2 = (gdouble)tmpLayerData.y2;

	}
	else if(pl_vals.resize_type == BOTTOM_RIGHT){
		_x1 = (gdouble)(tmpLayerData.x1-_w);
		_y1 = (gdouble)(tmpLayerData.y1-_h);
		_x2 = (gdouble)tmpLayerData.x2;
		_y2 = (gdouble)tmpLayerData.y2;
	}
	else {
		_x1 = (gdouble)(tmpLayerData.x1-(_w/2));
		_y1 = (gdouble)(tmpLayerData.y1-(_h/2));
		_x2 = (gdouble)(tmpLayerData.x2+(_w/2));
		_y2 = (gdouble)(tmpLayerData.y2+(_h/2));
	}

	if((_x2-_x1)<=0) _x2=_x1+1;
	if((_y2-_y1)<=0) _y2=_y1+1;
	gimp_item_transform_scale(layer,_x1, _y1,_x2, _y2);
}
//
static void rotateLayer(gint32 layer, gdouble angle, gint sN, gint rType){
	if(angle==0) return;

	gdouble newAngle = angle*3.14159/180;// to rad from grad
	gint _x = pl_vals.pX;
	gint _y = pl_vals.pY;

	//If not random
	if(rType == 0) newAngle = newAngle*(sN+1);

	//If Fixed coord
	if(pl_vals.rotate_coord_type == DINAMIC){
		LayerData tmpLayerData = getLayerData(layer);
		if(pl_vals.rotate_corner_type == TOP_LEFT){
			_x = tmpLayerData.x1;
			_y = tmpLayerData.y1;
		}
		else if(pl_vals.rotate_corner_type == TOP_RIGHT){
			_x = tmpLayerData.x2;
			_y = tmpLayerData.y1;
		}
		else if(pl_vals.rotate_corner_type == BOTTOM_LEFT){
			_x = tmpLayerData.x1;
			_y = tmpLayerData.y2;
		}
		else if(pl_vals.rotate_corner_type == BOTTOM_RIGHT){
			_x = tmpLayerData.x2;
			_y = tmpLayerData.y2;
		}
		else{
			_x = tmpLayerData.x1+(tmpLayerData.w/2);
			_y = tmpLayerData.y1+(tmpLayerData.h/2);
		}
	}

	// rotate direction:
	gimp_context_set_transform_direction(GIMP_TRANSFORM_FORWARD); //GIMP_TRANSFORM_BACKWARD

	gimp_item_transform_rotate(
			layer,
			newAngle,
			FALSE, //autocenter
			_x,    //center_x
			_y     //center_y
			);
	autocropLayer(layer, TRUE);
}
//
static void dropShadow(gint32 layer, gint32 angle, gint32 size, gint32 distance, GimpRGB color, gint32 opacity, gint sN){
	if(size == 0 && distance ==0) return;


	gdouble ang = ((angle + 180) * -1) * (M_PI / 180.0);
	gint offsetX = round(distance * cos(ang));
	gint offsetY = round(distance * sin(ang));

	if(sN==pl_vals.times-1)
		dropShadow(workLayer, angle,  size, distance, color,  opacity, -1);

	gint32 shadowlayer = gimp_layer_new(
			curImage,
			"_shadow_#0",
			gimp_image_width(curImage),
			gimp_image_height(curImage),
			GIMP_RGBA_IMAGE,
			opacity,
			GIMP_NORMAL_MODE
			);

	add_under_layer(shadowlayer, layer);

	gimp_selection_none(curImage);
	gimp_image_select_item(
						curImage,
						GIMP_CHANNEL_OP_REPLACE,
						layer
						);

	GimpRGB fgColor;
	gimp_context_get_foreground(&fgColor);
	gimp_context_set_foreground(&color);
	gimp_edit_fill(shadowlayer, GIMP_FOREGROUND_FILL);
	gimp_selection_none(curImage);

    gimp_layer_set_offsets(shadowlayer,offsetX,offsetY);
	blurLayer(shadowlayer, size, 0, 1);
	gimp_context_set_foreground(&fgColor);

	autocropLayer(shadowlayer, FALSE);

	LayerData tmpShadowLayer = getLayerData(shadowlayer);
	LayerData tmpWorkLayer = getLayerData(layer);

	LayerStack *layerItem = findLayerStack(layer);
		if(layerItem!=NULL){
		layerItem->margin_left=(tmpWorkLayer.x1-tmpShadowLayer.x1)>=0?(tmpWorkLayer.x1-tmpShadowLayer.x1):0;
		layerItem->margin_top=(tmpWorkLayer.y1-tmpShadowLayer.y1)>=0?(tmpWorkLayer.y1-tmpShadowLayer.y1):0;
		layerItem->margin_right=(tmpShadowLayer.x2-tmpWorkLayer.x2)>=0?(tmpShadowLayer.x2-tmpWorkLayer.x2):0;
		layerItem->margin_bottom=(tmpShadowLayer.y2-tmpWorkLayer.y2)>=0?(tmpShadowLayer.y2-tmpWorkLayer.y2):0;

		GList *l1 = g_list_find(clonedLayersList, layerItem);
		l1->data = layerItem;
		}

	//Rename layer and change id
	gchar *oldName = gimp_item_get_name(layer);
	gint32 newLayer = gimp_image_merge_down(curImage, layer,  GIMP_EXPAND_AS_NECESSARY);

	if(sN!=-1){
	LayerStack *lf;
	lf = findLayerStack(layer);
	GList *l = g_list_find(clonedLayersList, lf);
	lf->id = newLayer;
	l->data = lf;
	}
	else{
		workLayer = newLayer;
	}

	gimp_item_set_name(newLayer, oldName);

}

static void colorizeLayer(gint32 layer, gint hue, gint sat, gint light, gint sN, gint rType){
	if(hue==0) return;
	GimpParam    *return_vals;
	gint          nreturn_vals;
	float  l_hue = rType==1?hue:(hue*(sN+1));
	float  l_sat = sat;
	float  l_light = light;

	l_hue = l_hue>360?360:l_hue;
	l_hue = l_hue<0?0:l_hue;

	return_vals = gimp_run_procedure ("gimp-colorize",
		                         &nreturn_vals,
		                         GIMP_PDB_DRAWABLE, layer,
		                         GIMP_PDB_FLOAT, l_hue,
		                         GIMP_PDB_FLOAT, l_sat,
		                         GIMP_PDB_FLOAT, l_light,
		                         GIMP_PDB_END);
	if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
			          gimp_progress_end();
	else
		g_printf("Error on call gimp_run_procedure(%s)","gimp-colorize");

	return;
}

static void spreadLayer(gint32 layer,  gdouble radius, gint sN, gint rType){
	if(radius==0) return;
	GimpParam    *return_vals;
	gint          nreturn_vals;
	float  l_hor_radius = rType==1?radius:(radius*(sN+1));
	float  l_ver_radius = l_hor_radius;

    LayerData tmpCurLayer = getLayerData(layer);

    gdouble ramt = radius*2;
	gimp_layer_resize(layer,tmpCurLayer.w+ramt, tmpCurLayer.h+ramt, ramt/2, ramt/2);

	return_vals = gimp_run_procedure ("plug-in-spread",
		                         &nreturn_vals,
		                         GIMP_PDB_INT32, GIMP_RUN_NONINTERACTIVE,
		                         GIMP_PDB_IMAGE, curImage,
		                         GIMP_PDB_DRAWABLE, layer,
		                         GIMP_PDB_FLOAT, l_hor_radius,
		                         GIMP_PDB_FLOAT, l_ver_radius,
		                         GIMP_PDB_END);

	 if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS){
		          gimp_progress_end();

	             }
	 else
		 g_printf("Error on call gimp_run_procedure(%s)","plug-in-spread");
	 //autocropLayer(layer,TRUE);
	 return;
}

void add_under_layer(gint32 srclayer, gint32 dstlayer){
	gimp_image_insert_layer(
			curImage,
			srclayer,
			0,
			gimp_image_get_item_position(curImage, dstlayer) + 1);
}

