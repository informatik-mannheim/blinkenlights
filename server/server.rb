#!/usr/bin/env ruby
require 'socket'

TIME_PORT = 2000
ANIMATION_PORT = 2001

BLACK = 0
ON = 1
OFF = 2
KNIGHT_RIDER = 3
PRIDE = 4

class Animation
  attr_reader :start, :cycle_pause, :repeat, :steps

  def initialize(start, cycle_pause, repeat)
    @start = start
    @cycle_pause = cycle_pause
    @repeat = repeat
    @steps = []
  end

  def <<(step)
    @steps << step
  end

end

class Command

  attr_reader :duration, :command, :command_param

  def initialize(duration, command, command_param = 0)
    @duration = duration
    @command = command
    @command_param = command_param
  end
end


animation = Animation.new(
  10000, 0, 30
)

#animation << Command.new(0, KNIGHT_RIDER)
animation << Command.new(50, KNIGHT_RIDER, 0)
animation << Command.new(50, KNIGHT_RIDER, 1)
animation << Command.new(0, BLACK)


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

        puts "Send timestamp to client"
    end
end

xxx = t_stamp

t2 = Thread.new do
    server = TCPServer.new ANIMATION_PORT

    loop do
        client = server.accept

        id = client.recv(2)
        client.close_read

        puts "Request received. Client id=#{id}"

        client.write animation.start + xxx
        puts animation.start + xxx
        client.write "\n"
        client.write animation.cycle_pause
        puts animation.cycle_pause
        client.write "\n"
        client.write animation.repeat
        puts animation.repeat
        client.write "\n"
        client.write animation.steps.size
        puts animation.steps.size
        client.write "\n"

        animation.steps.each do |e|
          client.write e.duration
          puts e.duration
          client.write "\n"
          client.write e.command
          puts e.command
          client.write "\n"
          client.write e.command_param
          puts e.command_param
          client.write "\n"
        end

        client.close
    end
end

t1.join
t2.join
