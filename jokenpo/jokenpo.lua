--Initialize randomness!
math.randomseed(os.time())

--Moves and choices!
local moves = {"rock", "paper", "scissors"}
local res = 0
local mov = 0

--Function to get Rock/Paper/Scissors.
function get_move()
    return math.random(1, 3)
end

--Sleep function. Taken from lua wiki.
function sleep(s)
    local ntime = os.clock() + s/10
    repeat until os.clock() > ntime
end

--Here it is!
print("Rock-Paper-Scissors - The classic luck-based struggle!")
repeat 
    print("Choose a move!")
    print("Rock = 1, Paper = 2, Scissors = 3")
    res = io.read()
    if res == "1" or res == "2" or res == "3" then
        res_num = tonumber(res)
        print("Now me!")
        print("Jo..")
        sleep(10)
        print("Ken..")
        sleep(10)
        print("Po!")
        mov = get_move()
        if res_num == mov then
            print("Wow! Same move!")
        else
            if (res_num == 1 and mov == 2) or (res_num == 2 and mov == 3) or (res_num == 3 and mov == 1) then
                print("Hah!! " .. moves[mov] .. " beats " .. moves[res_num] .. "! You lose!")
            else
                print("Awww... " .. moves[res_num] .. " beats " .. moves[mov] .. "! You win..")
            end
        end
        sleep(30)
    end
    if res == "q" then
        print("Quitting now!")
    end
until res == "q"