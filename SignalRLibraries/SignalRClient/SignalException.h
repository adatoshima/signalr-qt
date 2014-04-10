/*
 *  Copyright (c) 2013-2014, p3root - Patrik Pfaffenbauer (patrik.pfaffenbauer@p3.co.at)
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *    Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright notice, this
 *    list of conditions and the following disclaimer in the documentation and/or
 *    other materials provided with the distribution.
 *
 *    Neither the name of the {organization} nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SIGNALEXCEPTION_H
#define SIGNALEXCEPTION_H

#include <QString>
#include <QMetaType>

namespace P3 { namespace SignalR { namespace Client {

class SignalException : public std::exception
{
public:
    enum SignalExceptionType
    {
        InvalidNegotiationValues = 0,
        InvalidProtocolVersion,
        EventStreamSocketLost,
        CouldNotEstablishConnection,
        ConnectionRefusedError,
        ServerClosedConnection,
        ServerRequiresAuthorization,
        SocketOperationTimedOut,
        RemoteHostClosedConnection,
        ContentNotFoundError,
        HostNotFoundError,
        OperationCanceled,
        UnknownNetworkError,
        InternalServerError,
        SslHandshakeFailed,
        UnkownError
    };

    SignalException();
    SignalException(const QString message, SignalExceptionType type);
    ~SignalException() throw();
    const char* what() const throw() ;

    SignalExceptionType getType()  { return _type; }
    const QString &getMessage() { return _message; }


private:
    const QString _message;
    SignalExceptionType _type;
};

}}}

Q_DECLARE_METATYPE(P3::SignalR::Client::SignalException*)

#endif // SIGNALEXCEPTION_H
