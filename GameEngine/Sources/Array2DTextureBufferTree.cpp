#include "Array2DTextureBufferTree.h"





ds::Array2DTextureBufferTree::Array2DTextureBufferTree()
{

}

ds::Array2DTextureBufferTree::Array2DTextureBufferTree(GLuint max_texture_size, GLuint min_texture_size, GLuint layer)
{
	this->max_texture_size = max_texture_size;
	this->min_texture_size = min_texture_size;

	this->height = (GLuint)(std::log2(max_texture_size) - std::log2(min_texture_size));
	this->layer = layer;

	for (GLuint i = 0, j = 1; i <= this->height; i++, j *= 4)
		this->no_of_segments += j;

	this->tree_segments = new ds::a2dtbt_seg[this->no_of_segments];

	this->build();
}


void ds::Array2DTextureBufferTree::build()
{
	GLuint nodes_idx = 0;

	this->tree = tree_segments + nodes_idx;
	this->tree->id = nodes_idx;
	nodes_idx++;

	buildSegment(nullptr, tree, this->max_texture_size, 0, 0, &nodes_idx, 0);
}

void ds::Array2DTextureBufferTree::buildSegment(ds::a2dtbt_seg *parent, ds::a2dtbt_seg *node, GLuint tex_size, GLuint x_coord, GLuint y_coord, GLuint *nodes_idx, GLuint height)
{
	node->parent = parent;
	node->tex_size = tex_size;
	node->layer = this->layer;
	node->x_coord = x_coord;
	node->y_coord = y_coord;

	/*node->position_x = x_coord / tex_size;
	node->position_y = y_coord / tex_size;
	node->max_positions = this->max_texture_size / tex_size;
	node->tex_offset_x = (1.0f / (GLfloat)node->max_positions) * (GLfloat)node->position_x;
	node->tex_offset_y = (1.0f / (GLfloat)node->max_positions) * (GLfloat)node->position_y;*/


	if (this->height == height) {
		for (GLuint i = 0; i < 4; i++)
			node->children[i] = nullptr;

		return;
	}

	for (GLuint i = 0; i < 4; i++)
	{
		GLuint child_x_offset = x_coord;
		GLuint child_y_offset = y_coord;

		if (i % 2 != 0)
			child_x_offset += tex_size / 2;
		if (i >= 2)
			child_y_offset += tex_size / 2;

		node->children[i] = tree_segments + *nodes_idx;
		node->children[i]->id = *nodes_idx;
		*nodes_idx += 1;

		buildSegment(node, node->children[i], tex_size / 2, child_x_offset, child_y_offset, nodes_idx, height + 1);
	}
}


ds::a2dtbt_seg* ds::Array2DTextureBufferTree::search(GLuint tex_size)
{
	return this->searchSegment(this->tree, tex_size, 0);
}

ds::a2dtbt_seg* ds::Array2DTextureBufferTree::searchSegment(ds::a2dtbt_seg *node, GLuint tex_size, GLuint height)
{
	if (node->available_children_paths == 0)
		return nullptr;

	if (node->tex_size == tex_size) {
		if ((node->available_children_paths >> 4) & 1)
		{
			node->available_children_paths = 0;
			return node;
		}
		else
			return nullptr;
	}

	if (this->height == height)
		return nullptr;

	for (GLuint i = 0; i < 4; i++)
	{
		ds::a2dtbt_seg *res = searchSegment(node->children[i], tex_size, height + 1);

		if (node->children[i]->available_children_paths == 0)
			node->available_children_paths &= ~(1 << i);

		if (res) {
			node->available_children_paths &= ~(1 << 4);
			return res;
		}
	}

	return nullptr;
}

void ds::Array2DTextureBufferTree::free(GLuint node_id)
{
	ds::a2dtbt_seg *node = &(this->tree_segments[node_id]);
	node->available_children_paths = 0x1F;

	freeSegment(node);
}

void ds::Array2DTextureBufferTree::freeSegment(ds::a2dtbt_seg *node)
{
	ds::a2dtbt_seg* parent = node->parent;

	if (node->parent == nullptr)
		return;

	for (GLuint i = 0; i < 4; i++)
	{
		if (parent->children[i] == node)
		{
			parent->available_children_paths |= 1 << i;
			break;
		}
	}

	if (parent->available_children_paths == 15)
		parent->available_children_paths |= 1 << 4;

	freeSegment(parent);
}