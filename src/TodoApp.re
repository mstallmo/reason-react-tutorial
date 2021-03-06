type item = {
  id: int,
  title: string,
  completed: bool
};

let str = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, children) => {
    ...component,
    render: (self) =>
      <div className="item">
        <input _type="checkbox" checked=(Js.Boolean.to_js_boolean(item.completed))
        /*TODO make interactive */
        />
        (str(item.title))
      </div>
  };
};

type state = {
  items: list(item)
};
type action = 
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");
let lastId = ref(0);
let newItem = () => {
  lastId := lastId^ + 1;
  {id: lastId^, title: "Click a button", completed: true}
};

let make = _children => {
  ...component,
  initialState: () => {
    items: [{
      id: 0, 
      title: "Write some things to do", 
      completed: false
    }]
  },
  reducer: (action, {items}) => 
    switch action {
    | AddItem => ReasonReact.Update({items: [newItem(),...items]})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (str("What to do"))
        <button onClick=(reduce((_evt) => AddItem))>(str("Add Something"))</button>
      </div>
      <div className="items"> 
        (
          ReasonReact.arrayToElement(Array.of_list(
            List.map((item) => <TodoItem key=(string_of_int(item.id)) item />, items)
          )) 
        )
      </div>
      <div className="footer">
        (numItems > 1 ? str(string_of_int(numItems) ++ " items") : str(string_of_int(numItems) ++ " item"))
      </div>
    </div>
  }
};
