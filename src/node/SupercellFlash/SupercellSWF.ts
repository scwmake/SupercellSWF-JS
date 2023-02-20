import * as util from "util";

import {
  type NATIVE_EXPORT,
  type NATIVE_SHAPE,
  NATIVE_SUPERCELL_SWF,
} from "../../native";
import { assert_item } from "../Utils/utils";
import { Vector } from "../Utils/Vector";

import { Export } from "./common/Export";
import { Shape } from "./tag/Shape";

export class SupercellSWF extends NATIVE_SUPERCELL_SWF {
  exports = new Vector<SupercellSWF, Export>(
    {
      getItem: function (index: number) {
        return assert_item<typeof NATIVE_EXPORT, Export>(
          this["__get_export_item__"](index),
          Export
        );
      },
      insertItem: this.__insert_export_item__,
      removeItem: this.__remove_export_item__,
      getLength: this.__get_exports_length__,
      setLength: this.__set_exports_length__,
    },
    this
  );

  shapes = new Vector<SupercellSWF, Shape>(
    {
      getItem: function (index: number) {
        return assert_item<typeof NATIVE_SHAPE, Shape>(
          this["__get_shape__"](index),
          Shape
        );
      },
      insertItem: this.__insert_shape__,
      removeItem: this.__remove_shape__,
      getLength: this.__get_shapes_length__,
      setLength: this.__set_shapes_length__,
    },
    this
  );

  [Symbol.toStringTag](): string {
    return "SupercellSWF";
  }

  [util.inspect.custom](): string {
    return `<${this[Symbol.toStringTag]()} >`;
  }

  toJSON(): object {
    return {
      useExternalTexture: this.useExternalTexture,
      useMultiResTexture: this.useMultiResTexture,
      useLowResTexture: this.useLowResTexture,
      multiResSuffix: this.multiResTextureSuffix,
      lowResSuffix: this.lowResTextureSuffix,
      shapes: this.shapes,
    };
  }
}
