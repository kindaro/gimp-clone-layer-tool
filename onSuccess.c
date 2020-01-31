/* clone-layer tool - plugin for GIMP * /

/*
 * onSuccess.c
 *
 *  Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */
static gint stopTerm =0;

static void onSuccess(){
	stopTerm++;
	if(stopTerm>10) {
		g_printf("Error recursive onSuccess()!");
		return;}

	//If autocrop layer:
	if(!pl_vals.is_autocrop){
		GList *l;
		for(l = g_list_last(clonedLayersList); l; l = l->prev){
			LayerStack *rl = l->data;
			gimp_layer_resize_to_image_size(rl->id);
		}
		gimp_layer_resize_to_image_size(workLayer);
	}

	//IF animate enable
	if(pl_vals.animate_enable){
		GList *l;
		for(l = g_list_last(clonedLayersList); l; l = l->prev){
			LayerStack *rl = l->data;
			gchar *lName = gimp_item_get_name(rl->id);
			gchar newName[256]="";
			gint iname = pl_vals.anim_tn;
			gint time = pl_vals.anim_nl;
			if(!l->prev){
				iname = pl_vals.anim_tf;
				time = pl_vals.anim_fl;
			}
			else if(!l->next){
				iname = pl_vals.anim_tl;
				time = pl_vals.anim_ll;
			}
			gchar *name="";
			if(iname==1)
				name="(combine)";
			if(iname==2)
				name="(replace)";

			sprintf(newName,"%s(%ims)%s",lName,
					time,
					name
					);
			gimp_item_set_name(rl->id, newName);
		}
	}

    if(g_list_first(clonedLayersList)){
    	//If add background:
    	if(pl_vals.add_bg){
    		GList *l;
    		GList *newLayersList=NULL;
    		gboolean workFilled = FALSE;
    		for(l = g_list_last(clonedLayersList); l; l = l->prev){
    			LayerStack *rl = l->data;
				if(pl_vals.add_bg_type == ADD_BG_BG || pl_vals.add_bg_type == ADD_BG_FG){
					if(!workFilled){
						//Apply layer opacity for work layer:
						gimp_image_set_active_layer(curImage, workLayer);
						gint32 tmpLayer = gimp_layer_new(
													curImage,
													"tmp",
													1,1,
													GIMP_RGBA_IMAGE,
													100,
													GIMP_NORMAL_MODE);
						gimp_image_insert_layer(curImage, tmpLayer, 0, -1);
						gint32 mergeLayer = gimp_image_merge_down(
												curImage,
												tmpLayer
												,GIMP_EXPAND_AS_NECESSARY);

						workLayer = mergeLayer;

						//Fill FG/BG color:
						gimp_image_select_item(
								curImage,
								GIMP_CHANNEL_OP_REPLACE,
								workLayer
								);
						gimp_selection_invert(curImage);
						gimp_edit_fill(workLayer, pl_vals.add_bg_type == ADD_BG_BG?GIMP_BACKGROUND_FILL:GIMP_FOREGROUND_FILL);
						gimp_selection_none(curImage);
						workFilled=!workFilled;
						}
///
					//Apply layer opacity for each layer:
					gimp_image_set_active_layer(curImage, rl->id);
					gint32 tmpLayer = gimp_layer_new(
							curImage,
							"tmp",
							1,1,
							GIMP_RGBA_IMAGE,
							100,
							GIMP_NORMAL_MODE);
					gimp_image_insert_layer(curImage, tmpLayer, 0, -1);
					gint32 mergeLayer = gimp_image_merge_down(
											curImage,
											tmpLayer
											,GIMP_EXPAND_AS_NECESSARY);

					gimp_image_select_item(
									curImage,
									GIMP_CHANNEL_OP_REPLACE,
									mergeLayer
									);
					gimp_selection_invert(curImage);
					gimp_edit_fill(mergeLayer, pl_vals.add_bg_type == ADD_BG_BG?GIMP_BACKGROUND_FILL:GIMP_FOREGROUND_FILL);
					gimp_selection_none(curImage);

					LayerStack *mergeLayerItem = g_new(LayerStack,1);
					mergeLayerItem->id=mergeLayer;
					newLayersList = g_list_prepend(
							newLayersList,
							mergeLayerItem
								);

				}

    		}
    		clonedLayersList = newLayersList?newLayersList:clonedLayersList;
    	}


		if(pl_vals.result_layes == MERGE_LAYERS){
			gint32 mergeLayer=0;
			GList *l;
			if(pl_vals.layer_order==DOWN_UP_ORDER){
						for(l = g_list_first(clonedLayersList); l; l = l->next){
							LayerStack *rl = l->data;
							gint32 rld=mergeLayer==0?rl->id:mergeLayer;
							if(l->next)
								mergeLayer = gimp_image_merge_down(
													curImage,
													rld
													,GIMP_EXPAND_AS_NECESSARY);
							else
								mergeLayer = gimp_image_merge_down(
												curImage,
												workLayer
												,GIMP_EXPAND_AS_NECESSARY);
						}
			}
			else{
				for(l = g_list_last(clonedLayersList); l; l = l->prev){
					LayerStack *rl = l->data;
					gint32 rld=mergeLayer==0?rl->id:mergeLayer;
						mergeLayer = gimp_image_merge_down(
											curImage,
											rld
											,GIMP_EXPAND_AS_NECESSARY);
				}
			}
				}
		else if (pl_vals.result_layes == GROUPING_LAYERS){
				//Grouping if nedded...
					groupLayer = gimp_layer_group_new(curImage);
					gimp_item_set_name(groupLayer, "CLT-GROUP");
					gimp_image_insert_layer(curImage, groupLayer, 0, -1);
					GList *l;
					if(pl_vals.layer_order == DOWN_UP_ORDER){

						for(l = g_list_last(clonedLayersList); l; l = l->prev){
							LayerStack *rl = l->data;
							gimp_image_reorder_item(curImage, rl->id, groupLayer, -1);
						}
						gimp_image_reorder_item(curImage, workLayer, groupLayer,-1);
					}
					else{
						gimp_image_reorder_item(curImage, workLayer, groupLayer,-1);
						for(l = g_list_first(clonedLayersList); l; l = l->next){
							LayerStack *rl = l->data;
							gimp_image_reorder_item(curImage, rl->id, groupLayer, -1);
						}
					}
		}
    }
    else{
    		onCloneClick();
    		onSuccess();
    }
workLayer=-1;
if(clonedLayersList){
	freeLayerStack(clonedLayersList);
	g_list_free(clonedLayersList);
	clonedLayersList=NULL;
}

}
