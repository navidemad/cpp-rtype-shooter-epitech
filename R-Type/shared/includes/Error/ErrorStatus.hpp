#pragma once

class ErrorStatus {

	// errors
	public:
		enum class Error {
			OK	= 0x00,
			KO	= 0x01,
			UNKNOWN
		};

	// ctor dtor
	public:
		ErrorStatus(void);
		~ErrorStatus(void);


	// copy / move operators
	public:
		ErrorStatus(const ErrorStatus &) = delete;
		ErrorStatus(const ErrorStatus &&) = delete;
		const ErrorStatus &operator=(const ErrorStatus &) = delete;
		const ErrorStatus &operator=(const ErrorStatus &&) = delete;

	// getter - setters
	public:
		bool	errorOccured(void) const;
		Error getErrorCode(void) const;
		void	setErrorCode(ErrorStatus::Error error);

	// attributes
	private:
		ErrorStatus::Error mError;

};
