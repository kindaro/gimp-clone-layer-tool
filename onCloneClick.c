/* clone-layer tool - plugin for GIMP * /

/*
 * onCloneClick.c
 *
 *  Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

void onCloneClick(){
	//Clear cloned list
    onUndoClick();
    //Run clone and transformation...
    LayerStack *itemLastLayer=NULL;
	int i;
	for(i=0; i<pl_vals.times; i++){
		gdouble curAngle = pl_vals.angle; //30
		gdouble curStepX = pl_vals.step_x;
		gdouble curStepY = pl_vals.step_y;
		gdouble curStepWidth = pl_vals.step_width;
		gdouble curStepHeight = pl_vals.step_height;
		gdouble curOpacity = pl_vals.opacity;
		gdouble curBlurRadius = pl_vals.blur_radius;
		gdouble curSpreadRadius = pl_vals.spread_radius;
		gdouble curColorizeHue =  pl_vals.colorize_hue;
		gint rType; // 0 - none; 1 - random X; 2 - random Y; 3 - both
		gint32 lastClonedLayer = -1;
		lastClonedLayer = cloneLayer(workLayer);

		//First Start Scale
		///////////////////////////////
		rType = 0;
		if(curStepHeight==0)
			if(pl_vals.ran_step_height_max!=0 || pl_vals.ran_step_height_min!=0){
				curStepHeight = getRandomRange(pl_vals.ran_step_height_min, pl_vals.ran_step_height_max);
				rType = 1;}
		if(curStepWidth == 0)
			if(pl_vals.ran_step_width_max!=0 || pl_vals.ran_step_width_min!=0){
				curStepWidth = getRandomRange(pl_vals.ran_step_width_min, pl_vals.ran_step_width_max);
				rType = rType==1?3:2;}

		itemLastLayer = g_list_last(clonedLayersList)->data;
		resizeLayer((gint32)itemLastLayer->id,
												curStepWidth, curStepHeight,i,rType);

		//Start Rotate layer:
		////////////////////////////
		rType = 0;
		if(curAngle == 0)
			if(pl_vals.random_angle_from!=0 || pl_vals.random_angle_to!=0){
				curAngle = getRandomRange(pl_vals.random_angle_from, pl_vals.random_angle_to);
				rType = 1;
			}
		rotateLayer(lastClonedLayer, curAngle, i, rType);


		//Start Blur
		/////////////////////////
		rType = 0;
		if(curBlurRadius == 0)
			if(pl_vals.random_blur_min!=0 || pl_vals.random_blur_max!=0){
				curBlurRadius = getRandomRange(pl_vals.random_blur_min, pl_vals.random_blur_max);
				rType = 1;
			}

		blurLayer(lastClonedLayer, curBlurRadius, i, rType);

		//Start transperensy
		////////////////////////////
		if(curOpacity==0){
			if(pl_vals.ran_step_opacity_max!=0 || pl_vals.ran_step_opacity_min!=0)
				curOpacity = getRandomRange(pl_vals.ran_step_opacity_min, pl_vals.ran_step_opacity_max);
		}
		else{
			curOpacity = getLayerData(lastClonedLayer).opacity+(pl_vals.opacity*(i+1));
		}
		opacityLayer(lastClonedLayer, curOpacity);

		//Colorize
		///////////////////////////////////////////
		rType = 0;
		if(curColorizeHue==0)
			if(pl_vals.random_hue_min!=0 || pl_vals.random_hue_max!=0){
				curColorizeHue = getRandomRange(pl_vals.random_hue_min, pl_vals.random_hue_max);
				rType = 1;
			}
		colorizeLayer(lastClonedLayer,curColorizeHue, pl_vals.colorize_sat,pl_vals.colorize_light, i, rType);

		//Noise Spread
		/////////////////////////////
		rType = 0;
		if(curSpreadRadius==0)
			if(pl_vals.random_spread_min!=0 || pl_vals.random_spread_max!=0){
				curSpreadRadius = getRandomRange(pl_vals.random_spread_min, pl_vals.random_spread_max);
				rType = 1;
			}
		spreadLayer(lastClonedLayer, curSpreadRadius, i, rType);

		//Drop Shadow:
		///////////////////////
		dropShadow(lastClonedLayer,
				pl_vals.shadow_angle,
				pl_vals.shadow_size,
				pl_vals.shadow_distance,
				pl_vals.shadow_color,
				pl_vals.shadow_opacity,
				i);


		//Start Move
		//////////////////////////////
		rType = 0;
		if(curStepX==0)
			if(pl_vals.ran_step_x_min!=0 || pl_vals.ran_step_x_max!=0){
				curStepX = getRandomRange(pl_vals.ran_step_x_min, pl_vals.ran_step_x_max);
				rType = 1;}
		if(curStepY==0)
			if(pl_vals.ran_step_y_min!=0 || pl_vals.ran_step_y_max!=0){
				curStepY = getRandomRange(pl_vals.ran_step_y_min, pl_vals.ran_step_y_max);
				rType = rType==1?3:2;}
		itemLastLayer = g_list_last(clonedLayersList)->data;
		moveLayer((gint32)itemLastLayer->id, curStepX, curStepY, i, rType);
	}

	gimp_displays_flush();
}

