#ifndef PARSE_H
# define PARSE_H

#include <regex>

#include "Instruction.hpp"
#include "Operand.hpp"

std::vector<IInstruction*> parse(std::string &str);

/**
 * If set == 1, set to true
 * If set == 0, set to false
 * else does not change the value of haserror and return it unchanged
 */
bool hasParseError(int set);

#endif
