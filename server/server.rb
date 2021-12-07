#!/usr/bin/env ruby
require 'socket'

TIME_PORT = 2000
ANIMATION_PORT = 2001

ON = 0
OFF = 1

animation = {
    start: 10000,
    cycle_pause: 10000,
    repeat: 10,
    elements: [
        { duration: 500,
          command: ON,
        },
        { duration: 500,
          command: OFF,
        },
        { duration: 1000,
          command: ON,
        },
        { duration: 1000,
          command: OFF,
        },
        { duration: 1000,
          command: ON,
        },
        { duration: 1000,
          command: OFF,
        },
        { duration: 500,
          command: ON,
        },
        { duration: 500,
          command: OFF,
        },
    ],
}

def t_stamp()
  t = Time.now
  hour = t.hour
  min = t.min
  sec = t.sec
  msec = (Time.now.to_f * 1000).to_i % 1000
  time_stamp = (hour * 60 * 60 * 1000) + (min * 60 * 1000) + (sec * 1000) + msec

  time_stamp
end


t1 = Thread.new do
    server = TCPServer.new TIME_PORT

    loop do
        client = server.accept
        client.write t_stamp
        client.write "\n"
        client.close
    end
end

xxx = t_stamp

t2 = Thread.new do
    server = TCPServer.new ANIMATION_PORT

    loop do
        client = server.accept

        client.write animation[:start] + xxx
        client.write "\n"
        client.write animation[:cycle_pause]
        client.write "\n"
        client.write animation[:repeat]
        client.write "\n"
        client.write animation[:elements].size
        client.write "\n"


        animation[:elements].each do |e|
          client.write e[:duration]
          client.write "\n"
          client.write e[:command]
          client.write "\n"
        end

        client.close
    end
end

t1.join
t2.join
