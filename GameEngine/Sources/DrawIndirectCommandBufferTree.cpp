#include "DrawIndirectCommandBufferTree.h"





ds::DrawIndirectCommandBufferTree::DrawIndirectCommandBufferTree()
{

}

ds::DrawIndirectCommandBufferTree::DrawIndirectCommandBufferTree(GLuint max_commands_no, GLuint min_commands_no)
{
	this->max_commands_no = max_commands_no;
	this->min_commands_no = min_commands_no;

	this->height = (GLuint)(std::log2(max_commands_no) - std::log2(min_commands_no));

	for (GLuint i = 0, j = 1; i <= this->height; i++, j *= 2)
		this->no_of_segments += j;

	this->tree_segments = new ds::dicbt_seg[this->no_of_segments];

	this->build();
}


void ds::DrawIndirectCommandBufferTree::build()
{
	GLuint nodes_idx = 0;

	this->tree = tree_segments + nodes_idx;
	this->tree->id = nodes_idx;
	nodes_idx++;

	buildSegment(nullptr, tree, 0, this->max_commands_no, &nodes_idx, 0);
}

void ds::DrawIndirectCommandBufferTree::buildSegment(ds::dicbt_seg *parent, ds::dicbt_seg *node, GLuint offset, GLuint commands_no, GLuint *nodes_idx, GLuint height)
{
	node->parent = parent;
	node->offset = offset;
	node->commands_no = commands_no;

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

		buildSegment(node, node->children[i], offset + i * commands_no / 2, commands_no / 2, nodes_idx, height + 1);
	}
}


ds::dicbt_seg* ds::DrawIndirectCommandBufferTree::search(GLuint commands_no)
{
	return this->searchSegment(this->tree, commands_no, 0);
}

ds::dicbt_seg* ds::DrawIndirectCommandBufferTree::searchSegment(ds::dicbt_seg *node, GLuint commands_no, GLuint height)
{
	if (node->available_children_paths == 0) {
		return nullptr;
	}

	if (node->commands_no / 2 < commands_no || this->height == height) {
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
		ds::dicbt_seg *res = searchSegment(node->children[i], commands_no, height + 1);

		if (node->children[i]->available_children_paths == 0)
			node->available_children_paths &= ~(1 << i);

		if (res) {
			node->available_children_paths &= ~(1 << 4);
			return res;
		}
	}

	return nullptr;
}


void ds::DrawIndirectCommandBufferTree::free(GLuint node_id)
{
	ds::dicbt_seg *node = &(this->tree_segments[node_id]);
	node->available_children_paths = 0x13;

	freeSegment(node);
}

void ds::DrawIndirectCommandBufferTree::freeSegment(ds::dicbt_seg *node)
{
	ds::dicbt_seg* parent = node->parent;

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

void ds::DrawIndirectCommandBufferTree::clean()
{
	delete[] this->tree_segments;

	this->tree_segments = new ds::dicbt_seg[this->no_of_segments];

	this->build();
}