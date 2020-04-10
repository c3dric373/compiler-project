#include <vector>
#include <string>
#include <iostream>

/** class Erreur
 */
class Erreur {

public:
    /**
     * @brief addErrorMessage
     * @param message the error's message
     *
     * Set error to true.
     * Concatenate the message to the errorMessage
     */
    void addErrorMessage(std::string message);

    /**
     * @brief getError
     * @return bool
     *
     * Return true if an error has been raised
     * Else return False
     */
    bool getError();

    /**
     * @brief getMessage
     * @return string, corresponding to the concatenation of
     * all of the messages that the Erreur contains
     */
    std::string getMessage();

private:
    /** boolean true if there is an error */
    bool error=false;

    /** errorMessage which is a concatenation of all errors'messages*/
    std::string errorMessage;

};

