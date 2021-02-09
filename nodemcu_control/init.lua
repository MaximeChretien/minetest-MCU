--[[
-- Basic mod to control Minetest using a NodeMCU
--]]

IP_ADDRESS = "X.X.X.X"

-- Node settings
POS_X = -80
POS_Y = 6
POS_Z = -100
NODE_TYPE = "mesecons_gates:not_on"

rqLedOn = false
rqLedOff = false

-- Loading HTTP API
local http_api = minetest.request_http_api()
if not http_api then
   print("ERROR: in minetest.conf, this mod must be in secure.http_mods!")
end

-- Placing node function
function place_node(res)
	-- Get the status of the button
	local place = tonumber(res.data)

	-- If the button is pushed, place the node
	if place == 1 then
		minetest.place_node({x=POS_X, y=POS_Y, z=POS_Z}, {name=NODE_TYPE})
	end
end

-- Event when the base node is activated by mesecon
function base_on(pos, node)
	-- Request a led change
	rqLedOn = true
end

-- Event when the base node is deactivated by mesecon
function base_off(pos, node)
	-- Request a led change
	rqLedOff = true
end

-- Register base node
minetest.register_node("nodemcu_control:base",
			{tiles = {"nodemcu_control_base.png"},
			groups = {oddly_breakable_by_hand=2},
			description="NodeMCUControl Base",
			-- Mesecons properties
			mesecons = {effector = {
				action_on = base_on,
				action_off = base_off
				}
			}}
		)

-- Main loop
function main()

	if rqLedOn then
		-- Send a request to enable the led
		http_api.fetch_async({url = "http://" .. IP_ADDRESS .. "/led_on", timeout = 1})
		rqLedOn = false
	elseif rqLedOff then
		-- Send a request to disable the led
		http_api.fetch_async({url = "http://" .. IP_ADDRESS .. "/led_off", timeout = 1})
		rqLedOff = false
	else
		-- Get the button status
		http_api.fetch({url = "http://" .. IP_ADDRESS .. "/place_node", timeout = 1}, place_node)
	end

	-- Ask Minetest to launch this function again after 200 ms
	minetest.after(0.2, main)
end

-- Main loop first call
main()
