#include "AutoTransport.h"

#include "WebSocketTransport.h"
#include "ServerSentEventsTransport.h"
#include "LongPollingTransport.h"
#include "Connection_p.h"

namespace P3 { namespace SignalR { namespace Client {

AutoTransport::AutoTransport() :
    HttpBasedTransport()
{
    _transports = QList<ClientTransport*>();
    _transports.append(new WebSocketTransport());
    //_transports.append(new ServerSentEventsTransport());
    _transports.append(new LongPollingTransport());

    _index = 0;
    _transport = 0;

}

AutoTransport::~AutoTransport()
{
    _transport = 0;
    qDeleteAll(_transports);
}

void AutoTransport::negotiate()
{
    foreach(ClientTransport *ct, _transports)
    {
        ct->setConnectionPrivate(_connection);
    }

    HttpBasedTransport::negotiate();
}

void AutoTransport::onNegotiatenCompleted(const NegotiateResponse& res)
{
    if(!res.tryWebSockets)
    {
        for(int i = _transports.size() -1; i >= 0; i--)
        {
            if(_transports[i]->getTransportType() == "webSockets")
            {
                _transports.removeAt(i);
            }
        }
    }
}

void AutoTransport::start(QString data)
{
    ClientTransport *transport = _transports[_index];
    _connection->emitLogMessage("Using transport '" + transport->getTransportType() +"'", SignalR::Info);
    connect(transport, SIGNAL(transportStarted(SignalException*)), this, SLOT(onTransportStated(SignalException*)));
    connect(transport, SIGNAL(onMessageSentCompleted(SignalException*)), this, SLOT(onMessageSent(SignalException*)));
    transport->start(data);

    if(_messages.count() > 0)
    {
        foreach(QString str, _messages)
        {
            transport->send(str);
        }

        _messages.clear();
    }
}

bool AutoTransport::abort(int timeoutMs)
{
    if(_transport)
    {
       return _transport->abort(timeoutMs);
    }
    return true;
}

void AutoTransport::send(QString data)
{
    if(_transport)
        _transport->send(data);
    else
        _messages.append(data);
}

void AutoTransport::retry()
{
    if(_transport)
        _transport->retry();
}

const QString &AutoTransport::getTransportType()
{
    static QString transport = "autoConnection";
    return transport;
}

void AutoTransport::onTransportStated(SignalException *e)
{
    if(e)
    {
        if(_index + 1 < _transports.count())
        {
            _index++;
            start("");
        }
        else
        {
            Q_EMIT transportStarted(e);
        }
    }
    else
    {
        _transport = _transports[_index];
        Q_EMIT transportStarted(e);
    }
}

void AutoTransport::onMessageSent(SignalException *ex)
{
    Q_EMIT onMessageSentCompleted(ex);
}

}}}
