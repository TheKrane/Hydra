#!/bin/bash

cat > include/$1.hpp << EOF
#pragma once

class $1
{
public:
    $1();
    ~$1();
};
EOF

cat > src/$1.cpp << EOF
#include "$1.hpp"

$1::$1()
{

}

$1::~$1()
{

}

EOF