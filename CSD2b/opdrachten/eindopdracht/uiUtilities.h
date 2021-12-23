//FROM: https://github.com/ciskavriezenga/CSD_21-22/tree/master/csd2b/theorie/xx_eindopdrachtExamples/06_choices

#pragma once

#include <iostream>

class UIUtilities
{
public:
  // returns the users choice, which depends on the passed selectionOptions
  static std::string retrieveSelection(std::string selectionOptions[],
    int numOptions);

  // returns the index of the users choice in the passed selectionOptions array
  static int retrieveSelectionIndex(std::string selectionOptions[],
    int numOptions);

  // returns the users input value, which has to be in the range of [min, max]
  static float retrieveValueInRange(float min, float max);

private:
  // hide default constructor and destructor
  // no need to instantiate object of class UIUtilities
  UIUtilities() {};
  ~UIUtilities() {};

  static bool validateSelection(std::string selection, std::string selectionOptions[],
      int numOptions);
  static std::string retrieveInput(std::string selectionOptions[], int numOptions);

};
