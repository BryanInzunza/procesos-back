import { Test, TestingModule } from '@nestjs/testing';
import { NativeController } from './native.controller';

describe('NativeController', () => {
  let controller: NativeController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [NativeController],
    }).compile();

    controller = module.get<NativeController>(NativeController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
