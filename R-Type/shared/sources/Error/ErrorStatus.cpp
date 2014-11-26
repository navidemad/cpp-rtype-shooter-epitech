#include "ErrorStatus.hpp"

ErrorStatus::ErrorStatus(ErrorStatus::Error error) : mError(error) {
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

ErrorStatus::ErrorStatus(const ErrorStatus &) {
}

const ErrorStatus &ErrorStatus::operator=(const ErrorStatus &) {
}
