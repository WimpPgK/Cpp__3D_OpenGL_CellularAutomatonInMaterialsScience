//-----------------------------------------------------------------------------
// basic.frag by Steve Jones 
// Copyright (c) 2015-2019 Game Institute. All Rights Reserved.
//
// Fragment shader for Part 1 of this tutorial
//-----------------------------------------------------------------------------
#version 330 core

in vec4 vert_color;
out vec4 frag_color;
void main()
{
    frag_color = vec4(vert_color);
    //frag_color = vec4(0.1f,0.0f,0.0f,1);
};