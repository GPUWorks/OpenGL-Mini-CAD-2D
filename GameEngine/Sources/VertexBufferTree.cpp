#include "VertexBufferTree.h"





ds::VertexBufferTree::VertexBufferTree()
{

}

ds::VertexBufferTree::VertexBufferTree(GLuint max_vertices_no, GLuint min_vertices_no)
{
	this->max_vertices_no = max_vertices_no;
	this->min_vertices_no = min_vertices_no;

	this->height = (GLuint)(std::log2(max_vertices_no) - std::log2(min_vertices_no));

	for (GLuint i = 0, j = 1; i <= this->height; i++, j *= 2)
		this->no_of_segments += j;

	this->tree_segments = new ds::vbt_seg[this->no_of_segments];

	this->build();
}


void ds::VertexBufferTree::build()
{
	GLuint nodes_idx = 0;

	this->tree = tree_segments + nodes_idx;
	this->tree->id = nodes_idx;
	nodes_idx++;

	buildSegment(nullptr, tree, 0, this->max_vertices_no, &nodes_idx, 0);
}

void ds::VertexBufferTree::buildSegment(ds::vbt_seg *parent, ds::vbt_seg *node, GLuint offset, GLuint vertices_no, GLuint *nodes_idx, GLuint height)
{
	node->parent = parent;
	node->offset = offset;
	node->vertices_no = vertices_no;

	if (this->height == height) {
		for (GLuint i = 0; i < 2; i++) {
			node->children[i] = nullptr;
		}

		return;
	}

	for (GLuint i = 0; i < 2; i++)
	{
		node->children[i] = tree_segments + *nodes_idx;
		node->children[i]->id = *nodes_idx;
		*nodes_idx += 1;

		buildSegment(node, node->children[i], offset + i * vertices_no / 2, vertices_no / 2, nodes_idx, height + 1);
	}
}


ds::vbt_seg* ds::VertexBufferTree::search(GLuint vertices_no)
{
	return this->searchSegment(this->tree, vertices_no, 0);
}

ds::vbt_seg* ds::VertexBufferTree::searchSegment(ds::vbt_seg *node, GLuint vertices_no, GLuint height)
{
	if (node->available_children_paths == 0) {
		return nullptr;
	}

	if (node->vertices_no / 2 < vertices_no || this->height == height) {
		if ((node->available_children_paths >> 4) & 1)
		{
			node->available_children_paths = 0;
			return node;
		}
		else
			return nullptr;
	}


	for (GLuint i = 0; i < 2; i++)
	{
		ds::vbt_seg *res = searchSegment(node->children[i], vertices_no, height + 1);

		if (node->children[i]->available_children_paths == 0)
			node->available_children_paths &= ~(1 << i);

		if (res) {
			node->available_children_paths &= ~(1 << 4);
			return res;
		}
	}

	return nullptr;
}


void ds::VertexBufferTree::free(GLuint node_id)
{
	ds::vbt_seg *node = &(this->tree_segments[node_id]);
	node->available_children_paths = 0x13;

	freeSegment(node);
}

void ds::VertexBufferTree::freeSegment(ds::vbt_seg *node)
{
	ds::vbt_seg* parent = node->parent;

	if (node->parent == nullptr)
		return;

	for (GLuint i = 0; i < 2; i++)
	{
		if (parent->children[i] == node)
		{
			parent->available_children_paths |= 1 << i;
			break;
		}
	}

	if (parent->available_children_paths == 3)
		parent->available_children_paths |= 1 << 4;

	freeSegment(parent);
}

void ds::VertexBufferTree::clean()
{
	delete[] this->tree_segments;

	this->tree_segments = new ds::vbt_seg[this->no_of_segments];

	this->build();
}