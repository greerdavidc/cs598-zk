#include "node.h"

using namespace std;

Node::Node() {
    color = 0;
    randkey = 0;
}

Node::Node(int col) {
    color = col;
}

bool Node::GenHash() {
    unsigned char input[12];
    memcpy(input, &color, 4);
    memcpy(input+4, &randkey, 8);

    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, input, 12))
        return false;

    if(!SHA256_Final(commithash, &context))
        return false;
    return true;
}

bool Node::VerHash() {
    unsigned char checkhash[SHA256_DIGEST_LENGTH];
    unsigned char input[12];
    memcpy(input, &color, 4);
    memcpy(input+4, &randkey, 8);

    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, input, 12))
        return false;

    if(!SHA256_Final(checkhash, &context))
        return false;
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        if(checkhash[i] != commithash[i])
            return false;
    }
    return true;
}

void Node::Randomize(int32_t* colormap) {
    if(0 == color)
        color = (rand() % 3) + 1;
    else
        color = colormap[color-1];
    randkey = (uint64_t)rand();
}