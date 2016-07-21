/**
 * Created by KICT-12 on 2016-07-19.
 */

const net = require('net');
const PORT = 8080;

let object_list = [{
    x : 30,
    y : 20
}];

let sockets = [];

net.createServer((socket)=> {

    console.log('connect :' + socket.remoteAddress +':'
        + socket.remotePort
    );

    sockets.push({
        address : socket.remoteAddress,
        socket : socket,
    });

    socket.on('error',(evt)=>{
        console.log(evt);
    });
    socket.on('close',(evt)=>{
        console.log('connection closed!');
        console.log(evt);
    });
    socket.on('data',(evt)=>{
        //2byte : header(1004)
        //2byte : 요청 type
        //extra :...
        data = evt;

        let header = data.readInt16LE(0);
        let req_type = data.readInt16LE(2);
        if(header == 1004) {
            switch (req_type) {
                case 100: //로그인 요청
                    break;
                case 200: //위치정보 전송
                {
                    let index = data.readInt16LE(4);
                    sockets[index].x = data.readFloatLE(8);
                    sockets[index].y = data.readFloatLE(12);
                    //console.log(sockets);

                    let buff = new Buffer(20);
                    buff.writeInt16LE(1004,0);
                    buff.writeInt16LE(100,2); //recv position
                    console.log("send data " + sockets.length);
                    if(sockets.length >= 2) {
                        buff.writeFloatLE(sockets[0].x,4);
                        buff.writeFloatLE(sockets[1].x,8);
                        buff.writeFloatLE(sockets[0].y,12);
                        buff.writeFloatLE(sockets[1].y,16);

                        console.log(buff);

                        for(let i=0;i<sockets.length;i++ ) {
                            sockets[i].socket.write(buff);
                        }
                    }
                    else {
                        console.log('wait player');
                    }


                }
                    break;
            }
        }
        else {
            console.log('packet error');
        }

        console.log('header :' + header);
        console.log('request type :' + req_type);

    });

}).listen(PORT);

console.log('server listen :' + PORT);
