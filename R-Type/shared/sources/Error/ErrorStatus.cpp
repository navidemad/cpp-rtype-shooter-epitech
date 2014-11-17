#include "ErrorStatus.hpp"

ErrorStatus::ErrorStatus(void) : mError(ErrorStatus::Error::OK) {
}

ErrorStatus::~ErrorStatus(void) {
}

bool	ErrorStatus::errorOccured(void) const {
	return mError != ErrorStatus::Error::OK;
}

ErrorStatus::Error ErrorStatus::getErrorCode(void) const {
	return mError;
}

void	ErrorStatus::setErrorCode(ErrorStatus::Error error) {
	mError = error;
}
