#include "IdeaState.h"
#include "global.h"

IdeaState::IdeaState(
  double power
) {
  this->local_power = power;
  this->local_poison_amount = 0;
  this->local_poison_production = 0;
}

double IdeaState::get_local_power() { return this->local_power; }
void IdeaState::set_local_power(double power) { this->local_power = power; }
double IdeaState::get_local_poison_amount() {
  return this->local_poison_amount;
}
void IdeaState::set_local_poison_amount(double poison_amount) {
  this->local_poison_amount = poison_amount;
}

void IdeaState::produce_poison_local() {
  determine_poison_production();
  this->local_poison_amount += this->local_poison_production;
}

void IdeaState::determine_poison_production() {
  // ToDo: Test if this works as expected
  this->local_poison_production = normal_distribution_pdf(this->local_power);
}

void IdeaState::change_local_power(double value) { this->local_power += value; }

bool IdeaState::is_local_poison_amount_above_quorum() {
  double quorum = 10;
  return this->local_poison_amount >= quorum;
}

void IdeaState::set_poison_zero() {
  this->local_poison_amount = 0;
}