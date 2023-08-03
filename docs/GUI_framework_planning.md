# GUI Framework Planning
Temporary notepad

## Basic structure
- Screen is split into 8 pixel high rows (unlimited amount, can scroll)
- Each row gets a pointer to a GraphicsObject class
- Each GraphicsObject class does its own drawing in its own framebuffer, gets copied to the screen by graphics manager code
- Selectable GraphicsObjects can be selected with up/down keys

## Possible API
### GraphicsObject
Public functions:
#### void update()
Process an update, return when framebuffer ready.
#### bool isSelectable()
Returns true if item can be selected, false otherwise
#### void select()
Tells the GraphicsObject that it is selected.
#### void input(char key)
Sends an input to the GraphicsObject - this is used so up/down keys and cancel still work. The inputted key will be gathered from IME (when that is implemented)
#### void commit()
Tells the GraphicsObject to write any variables they need to before they are destroyed.
#### int getHeight()
Gets the requested amount of rows for this GraphicsObject. Cannot be more than 1 screenful.
Private functions:
#### draw_pixel(uint16_t x, uint16_t y, int value)
Draw a pixel on the GraphicsObject.
#### draw_character(uint16_t x, uint16_t y, char character, int value)
Draw a single character on the GraphicsObject.
#### draw_text(uint16_t x, uint16_t y, uint16_t width, char* text, int value)
Draw text on the GraphicsObject. If the width is longer than `width`, scroll with the clock.
#### draw_hline(uint16_t y, int value);
Draw a horizontal line across the whole GraphicsObject.
#### draw_vline(uint16_t x, int value)
Draw a vertical line across the whole GraphicsObject.
#### fill(int value)
Completely fill the GraphicsObject.

### Graphics Manager
#### void gui_add_graphicsobject(GraphicsObject ob)
Add a GraphicsObject to the next free line on screen.
#### void gui_clear()
Clear all lines.
#### void gui_enter()
Starts the currently designed UI. Returns when user presses cancel or gui_exit() is called.
#### void gui_exit()
Signals to the manager to exit the GUI cleanly
#### int gui_max_height()
Gets the maximum amount of rows a single object can take up.

## Possible GraphicsObjects provided by default
### Label
Just a string of text.
### TextInput
Get one line of text.
### MultilineInput
Get several lines of text.
### Selector
Select a value. Interrupt when receiving an OK character for input, and use the whole screen to draw a selection menu.